#ifndef _DANISH_H_
#define _DANISH_H_

#include <stdint.h>

#define DANISH_MAX_DATA_SIZE		196
#define DANISH_MAX_PACKET_SIZE		DANISH_MAX_DATA_SIZE + 7

typedef enum {
	PACKET_ADDRESS,
	PACKET_FUNCTION,
	PACKET_REG_ID_MSB,
	PACKET_REG_ID_LSB,
	PACKET_LEN,
} packet_params_enu;

typedef enum {
	FUNC_WRITE,
	FUNC_WRITE_ACK,
	FUNC_READ,
	FUNC_READ_ACK
} function_enu;

typedef struct {
	uint8_t address;
	function_enu function;
	uint16_t regID;
	uint8_t len;
	uint8_t *data;
} danish_st;

uint8_t danish_make(uint8_t address, function_enu function, uint16_t regID, uint8_t len, uint8_t *data, uint8_t *packet);

int8_t danish_ach(uint8_t *packet, uint8_t len, danish_st *result);

void danish_yiq(uint8_t c);

#endif
