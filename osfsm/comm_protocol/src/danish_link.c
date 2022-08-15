#include <danish_link.h>

static uint8_t number_of_registered_ids = 0;
static void (*danish_link_write_interface)(uint8_t *data, uint8_t size);
static uint8_t req_flag = 0;
static uint8_t tx_buffer[DANISH_MAX_PACKET_SIZE];
static uint16_t tx_len;

typedef enum {
	DANISH_LINK_FLAGS_WRITE = 0x01,
	DANISH_LINK_FLAGS_READ = 0x02,
} danish_link_flags_enu;

int8_t danish_add_register(uint16_t regID, uint8_t *pbuf, uint8_t size, filled_callback_ptr filled_callback,
	       read_callback_ptr read_callback)
{
	if (number_of_registered_ids >= DANISH_LINK_MAX_REGISTERS)
		return -1;

	registers[number_of_registered_ids].regID = regID;
	registers[number_of_registered_ids].ptr = pbuf;
	registers[number_of_registered_ids].filled_callback = filled_callback;
	registers[number_of_registered_ids].read_callback = read_callback;
	registers[number_of_registered_ids].size = size;
	registers[number_of_registered_ids].flags = 0;
	
	number_of_registered_ids++;

	return 1;
}

static link_reg_st* find_register_inf(uint16_t regID) {
	for (uint8_t i = 0; i < number_of_registered_ids; i++) {
		if (registers[i].regID == regID)
			return &registers[i];
	}
	return NULL;
}

int8_t danish_req_reg_write(uint8_t addr, uint16_t regID, uint8_t *data) {
	//find register
	link_reg_st *reg = find_register_inf(regID);
	if (reg == NULL) return -1;

	if (reg->flags & DANISH_LINK_FLAGS_WRITE) return 0;

	reg->waddr = addr;
	memcpy(reg->ptr, data, reg->size);
	reg->flags |= DANISH_LINK_FLAGS_WRITE;

	req_flag = 1;

	return 1;
}

int8_t danish_req_reg_read(uint8_t addr, uint16_t regID) {
	//find register
	link_reg_st *reg = find_register_inf(regID);
	if (reg == NULL) return -1;

	if (reg->flags & DANISH_LINK_FLAGS_READ) return 0;

	reg->raddr = addr;
	reg->flags |= DANISH_LINK_FLAGS_READ;

	req_flag = 1;

	return 1;
}

void danish_link_init(void (*write_interface)(uint8_t *data, uint16_t len)) {
	danish_link_write_interface = write_interface;
}

static uint8_t has_req() {
	return req_flag;
}


void danish_machine() {
	static uint8_t read = 0;
	static uint8_t state = 0;
	static danish_st rcv_packet;

	if (state == 0) {
		int8_t fret = danish_parse(&rcv_packet);
		if (fret == 1) {
			for (int i = 0; i < number_of_registered_ids; i++) {
				if (rcv_packet.address == 1) {	//FIXME : 1 is my own address on bus
					printf("Packet rx from %d : func(%d) - reg(%d)\r\n",
							rcv_packet.address, rcv_packet.function, rcv_packet.regID);

					if (rcv_packet.function == FUNC_WRITE) {
						memcpy(registers[i].ptr, rcv_packet.data, registers[i].size);
						if (registers[i].filled_callback != NULL) {
							registers[i].filled_callback(rcv_packet.address);
						}
						//must transmit write ack
						uint8_t write_ack_packet[20];
						uint16_t size = danish_make(rcv_packet.address, FUNC_WRITE_ACK, rcv_packet.regID, 0, NULL, write_ack_packet);
						danish_link_write_interface(write_ack_packet, size);										
					} else if (rcv_packet.function == FUNC_WRITE_ACK) {
						printf("Write ack received\r\n");
						registers[i].flags &= ~DANISH_LINK_FLAGS_WRITE;
					} else if (rcv_packet.function == FUNC_READ) {
						danish_req_reg_write(rcv_packet.address, rcv_packet.regID, registers[i].ptr);
						if (registers[i].read_callback != NULL) {
							registers[i].read_callback(rcv_packet.address);
						}
					}
				}
			}
		} else {
			for (int i = 0; i < number_of_registered_ids; i++) {
				if (registers[i].flags & DANISH_LINK_FLAGS_WRITE) {
					//prepare packet
					printf("Write requset reg %d on device %d\r\n",
							registers[i].regID, registers[i].waddr);
					tx_len = danish_make(registers[i].waddr, FUNC_WRITE, registers[i].regID,
						registers[i].size, registers[i].ptr, tx_buffer);
					read = 0;
					registers[i].flags &= ~DANISH_LINK_FLAGS_WRITE;
					state = 1;
	
				} else if (registers[i].flags & DANISH_LINK_FLAGS_READ) {
					printf("Read request from %d with reg %d\r\n", 
							registers[i].raddr, registers[i].regID);
					tx_len = danish_make(registers[i].raddr, FUNC_READ, registers[i].regID,
							0, NULL, tx_buffer);
					read = 1;
					registers[i].flags &= ~DANISH_LINK_FLAGS_READ;
					state = 1;
				}
			}
		}
	} else if (state == 1) {
		danish_link_write_interface(tx_buffer, tx_len);
		state = 0;
	} else if (state == 2) {
		//wait for response (write or read)

	}
}
