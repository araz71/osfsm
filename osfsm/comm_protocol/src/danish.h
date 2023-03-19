#ifndef _DANISH_H_
#define _DANISH_H_

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <delay.h>
#include <danish_conf.h>

#ifndef DANISH_MAX_DATA_SIZE
#error "Please define DANISH_MAX_DATA_SIZE"
#endif

#define DANISH_MAX_PACKET_SIZE		DANISH_MAX_DATA_SIZE + 7

typedef enum {
	PACKET_ADDRESS,
	PACKET_FUNCTION,
	PACKET_REG_ID_MSB,
	PACKET_REG_ID_LSB,
	PACKET_LEN,
	PACKET_DATA,
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

/*
 * return
 * 	1 	: successfull
 *	0 	: failed
 */
int danish_parse(danish_st *packet);

#ifdef DANISH_STATS
uint32_t danish_stats_get_successfull_received();
uint32_t danish_stats_get_checksum_error();
uint32_t danish_stats_get_full_error();
#endif

#endif
