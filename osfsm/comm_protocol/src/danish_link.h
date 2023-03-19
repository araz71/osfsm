#ifndef DANISH_LINK_H_
#define DANISH_LINK_H_

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <danish_conf.h>
#include <danish.h>
#include <log.h>

#ifndef DANISH_LINK_MAX_REGISTERS
#error "Please define DANISH_LINK_MAX_REGISTERS to show how many registers you have"
#endif

#ifndef DANISH_LINK_MAX_REGISTERS
#error "please define maximum registers avaliable(DANISH_LINK_MAX_REGISTERS)"
#endif

typedef enum {
	DANISH_LINK_FLAGS_WRITE = 0x01,
	DANISH_LINK_FLAGS_READ 	= 0x02,
} danish_link_flags_enu;

typedef void (*filled_callback_ptr)(uint8_t);
typedef void (*read_callback_ptr)(uint8_t);

typedef struct  {
	uint16_t regID;		// RegisterID
	uint8_t flags;		// Flags for read/write request
	uint8_t *ptr;		// Pointer of buffer which will read or write in.
	uint8_t size;		// Size of buffer

	uint8_t rwaddr;		// Address of module which we want to read/write

	void (*filled_callback)(uint8_t writer);	// Will call when buffer is filled by writer
	uint8_t* (*read_callback)(uint8_t reader);		// Will call when a reader read buffer
	void (*write_ack_callback)();			// Will call when destination returns write callback
} link_reg_st;

int8_t danish_add_register(link_reg_st *reg);

int8_t danish_write(uint8_t addr, uint16_t regID, uint8_t *data);
int8_t danish_read(uint8_t addr, uint16_t regID);

void danish_link_init(uint8_t address, void(*write_interface)(uint8_t* data, uint16_t len));

void danish_machine();

#endif
