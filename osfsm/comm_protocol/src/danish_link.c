#include <danish_link.h>

static uint8_t number_of_registered_ids = 0;
static void (*write_callback_ptr)(uint8_t *data, uint8_t size, void (*transmitted_cb)(int8_t tx));

void danish_add_register(uint16_t regID, uint8_t *pbuf, uint8_t size, filled_callback_ptr filled_callback,
	       read_callback_ptr read_callback)
{
	if (number_of_registered_ids >= DANISH_LINK_MAX_REGISTERS)
		return;

	registers[number_of_registered_ids].regID = regID;
	registers[number_of_registered_ids].ptr = pbuf;
	registers[number_of_registered_ids].filled_callback = filled_callback;
	registers[number_of_registered_ids].read_callback = read_callback;
	registers[number_of_registered_ids].size = size;
	registers[number_of_registered_ids].flags = 0;
}

static link_reg_st* find_register_inf(uint16_t regID) {
	for (uint8_t i = 0; i < number_of_registered_ids; i++) {
		if (registers[i].regID == regID)
			return &registers[i];
	}
	return NULL;
}

void danish_req_reg_write(uint16_t regID, uint8_t *data) {
	//find register
	link_reg_st *reg = find_register_inf(regID);
	if (reg == NULL) return;

	memcpy(reg->ptr, data, reg->size);
	reg->flags |= 1;
}

void danish_req_reg_read(uint16_t regID, void (*callback(int8_t ack))) {
	//find register
	link_reg_st *reg = find_register_inf(regID);
	if (reg == NULL) return;

	reg->flags |=2;
}

void danish_register_output(void (*write_cb)(uint8_t *data, uint8_t size, void (*transmitted_cb)(int8_t tx))) {
	write_callback_ptr = write_cb;	
}

void danish_machine() {
	//states:
	//	0: loop on every register
	//	1: transmitting
	//	2: wait for transmitting
	//	3: wait for ack
}
