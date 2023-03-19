#include <danish_link.h>

link_reg_st __attribute__((weak)) registers[DANISH_LINK_MAX_REGISTERS];
static uint8_t number_of_registered_ids = 0;
static void (*danish_writer)(uint8_t *data, uint16_t size);
static uint8_t danish_address;

static uint8_t tx_buffer[DANISH_MAX_PACKET_SIZE];
static uint16_t tx_len;

int8_t danish_add_register(link_reg_st *reg)
{
	if (number_of_registered_ids >= DANISH_LINK_MAX_REGISTERS)
		return -1;

	for (int i = 0; i < DANISH_LINK_MAX_REGISTERS; i++) {
		if (registers[i].regID == reg->regID)
			return -1;	// Repetetive register id
	}

	reg->rwaddr = 0;
	reg->flags = 0;

	memcpy((uint8_t*)&registers[number_of_registered_ids], (uint8_t*)reg, sizeof(link_reg_st));

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

int8_t danish_write(uint8_t addr, uint16_t regID, uint8_t *data) {
	//find register
	link_reg_st *reg = find_register_inf(regID);
	if (reg == NULL) return -1;	// Unknow register id
	if (reg->flags) return 0;	// Busy for read/write

	reg->rwaddr = addr;
	memcpy(reg->ptr, data, reg->size);
	reg->flags |= DANISH_LINK_FLAGS_WRITE;

	return 1;
}

int8_t danish_read(uint8_t addr, uint16_t regID) {
	//find register
	link_reg_st *reg = find_register_inf(regID);
	if (reg == NULL) return -1;	// Unknown register id
	if (reg->flags) return 0;	// Busy for read/write

	reg->rwaddr = addr;
	reg->flags |= DANISH_LINK_FLAGS_READ;

	return 1;
}

void danish_link_init(uint8_t address, void (*write_interface)(uint8_t *data, uint16_t len)) {
	danish_writer = write_interface;
	danish_address = address;
}

void danish_machine() {
	static uint8_t read = 0;
	static uint8_t request_busy= 0;
	static danish_st rcv_packet;

	int8_t fret = danish_parse(&rcv_packet);
	if (fret == 1) {
		for (int i = 0; i < number_of_registered_ids; i++) {
			if (rcv_packet.address == danish_address) {
				mlog("Packet from %d : func(%s) - reg(%d)\r\n",
					rcv_packet.address, 
					rcv_packet.function == FUNC_WRITE ? "wr" : 
						(rcv_packet.function == FUNC_WRITE_ACK ? "w-ack" : "r"),
					rcv_packet.regID);

				// Incomming packet request to write.
				if (rcv_packet.function == FUNC_WRITE) {
					memcpy(registers[i].ptr, rcv_packet.data, registers[i].size);

					if (registers[i].filled_callback != NULL)
						registers[i].filled_callback(rcv_packet.address);

					// Make Write ack. so writer will sure about writing.
					uint8_t write_ack_packet[20];
					uint16_t size = danish_make(rcv_packet.address, FUNC_WRITE_ACK, rcv_packet.regID, 0, NULL, write_ack_packet);
					danish_writer(write_ack_packet, size);	

				} else if (rcv_packet.function == FUNC_WRITE_ACK) {
					registers[i].write_ack_callback();

				// Read request will answer by FUNC_WRITE
				} else if (rcv_packet.function == FUNC_READ) {
					danish_write(rcv_packet.address, rcv_packet.regID, registers[i].ptr);
					if (registers[i].read_callback != NULL) {
						registers[i].read_callback(rcv_packet.address);
					}
				}
			}
		}
		// Check for any Read/Write request
	} else {
		for (int i = 0; i < number_of_registered_ids; i++) {
			if (registers[i].flags & DANISH_LINK_FLAGS_WRITE) {
				//prepare packet
				mlog("Write requset reg %d on device %d\r\n",
						registers[i].regID, registers[i].rwaddr);
				tx_len = danish_make(registers[i].rwaddr, FUNC_WRITE, registers[i].regID,
					registers[i].size, registers[i].ptr, tx_buffer);
				
				read = 0;
				registers[i].flags &= ~DANISH_LINK_FLAGS_WRITE;
				request_busy = 1;
	
			} else if (registers[i].flags & DANISH_LINK_FLAGS_READ) {
				mlog("Read request from %d with reg %d\r\n", 
						registers[i].rwaddr, registers[i].regID);
				tx_len = danish_make(registers[i].rwaddr, FUNC_READ, registers[i].regID,
						registers[i].size, registers[i].ptr, tx_buffer);
				read = 1;
				registers[i].flags &= ~DANISH_LINK_FLAGS_READ;
				request_busy = 1;
			}

			if (request_busy == 1) {
				danish_writer(tx_buffer, tx_len);
				request_busy = 0;
			}
		}
	}
}
