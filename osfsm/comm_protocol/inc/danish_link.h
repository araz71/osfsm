#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <danish.h>

#define DANISH_LINK_MAX_REGISTERS	10

#ifndef DANISH_LINK_MAX_REGISTERS
#error "please define maximum registers avaliable"
#endif

typedef void (*filled_callback_ptr)(uint8_t);
typedef void (*read_callback_ptr)(uint8_t);

typedef struct  {
	uint16_t regID;
	uint8_t flags;
	uint8_t *ptr;
	uint8_t size;

	uint8_t raddr;
	uint8_t waddr;

	void (*filled_callback)(uint8_t writer);
	void (*read_callback)(uint8_t reader);
} link_reg_st;

link_reg_st registers[DANISH_LINK_MAX_REGISTERS];

int8_t danish_add_register(uint16_t regID, uint8_t *pbuf, uint8_t size, filled_callback_ptr filled_callback,
	read_callback_ptr read_callback);

int8_t danish_req_reg_write(uint8_t addr, uint16_t regID, uint8_t *data);
int8_t danish_req_reg_read(uint8_t addr, uint16_t regID);
