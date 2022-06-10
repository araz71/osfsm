#include <stdint.h>

#ifndef DANISH_LINK_MAX_REGISTERS
#error "please define maximum registers avaliable"
#endif

typedef void (*)(void)	filled_callback_ptr;
typedef void (*)(uint8_t *, uint8_t *)	read_callback_ptr;

typedef struct link_reg_st {
	uint16_t regID;
	uint8_t flags;
	uint8_t *ptr;
	uint8_t size;

	void (*filled_callback)(void);
	void (*read_callback(uint8_t *ret, uint8_t *size);
}

link_reg_st registers[DANISH_LINK_MAX_REGISTERS];

void danish_add_register(uint16_t regID, uint8_t *pbuf, uint8_t size, filled_callback_ptr filled_callback,
	read_callback_ptr read_callback);

void danish_req_reg_write(uint16_t regID, uint8_t *data);
void danish_req_reg_read(uint16_t regID, void (*callback)(int8_t ack));
