#define DANISH_STATS
#include "danish.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define Test_iter	2000

#define mlog(...) {	printf("%d : ", __LINE__);	\
	printf(__VA_ARGS__);	\ 
	error = 1;}

int main() {
	uint8_t error = 0;
	int failed_cntr = 0;
	int succ_cntr = 0;
	srand(time(NULL));

	for (int i = 0; i < Test_iter; i++) {
		error = 0;

		uint16_t data_size = rand() % DANISH_MAX_DATA_SIZE;
		uint8_t *data = malloc(data_size);
		
		for (int byte_cntr = 0; byte_cntr < data_size; byte_cntr++) {
			data[byte_cntr] = rand();
		}
		
		function_enu func = rand() % 4;
		uint8_t address = rand();
		uint16_t reg = rand();
		uint8_t *result = malloc(DANISH_MAX_PACKET_SIZE);
		
		uint16_t result_size = danish_make(address, func, reg, data_size, data, result);

		if (result_size == 0) mlog("Create Packet : Packet size is zero\r\n");
		if (result_size < (data_size + 7)) mlog("Create Packet : Packet size error(must : %d - is : %d)\r\n", (data_size + 7), result_size);
		if (result[PACKET_ADDRESS] != address) mlog("Create Packet : Address mismatch(must : %d - is : %d)\r\n", address, result[PACKET_ADDRESS]);
		if (result[PACKET_FUNCTION] != func) mlog("Create Packet : Function mismatch(must : %d - is : %d)\r\n", func, result[PACKET_FUNCTION]);
		if (result[PACKET_REG_ID_MSB] != (reg >> 8)) mlog("Create Packet : MSB of Register mismatch(must : %d - is : %d)\r\n", reg >> 8, result[PACKET_REG_ID_MSB]);
		if (result[PACKET_REG_ID_LSB] != (reg & 0xff)) mlog("Create Packet : LSB of Register mismatch(must : %d - is : %d)\r\n", reg & 0xff, result[PACKET_REG_ID_LSB]);
		if (result[PACKET_LEN] != data_size) mlog("Create Packet : Data size mismatch(must : %d - is : %d)\r\n", data_size, result[PACKET_LEN]);		
		if (memcmp(&result[PACKET_DATA], data, data_size) != 0) mlog("Create Packet : Packet data mismatch\r\n");

		//indi ach
		danish_st params;
		int fret = danish_ach(result, result_size, &params);
		if (fret == 0) mlog("Packet incomplte!\r\n");
		if (fret == -1) mlog("Packet Checksum error\r\n");

		if (params.address != address) mlog("Open packet : Address mismatch(must : %d - is : %d)\r\n", address, params.address);
		if (params.function != func) mlog("Open packet : Function mismatch(must : %d - is : %d)\r\n", func, params.function);
		if (params.regID != reg) mlog("Open packet : Register mismatch(must : %d - is : %d\r\n", reg, params.regID);
		if (params.len != data_size) mlog("Open packet : Data-len mismatch(must : %d - is : %d\r\n", data_size, params.len);
		if (memcmp(params.data, data, data_size) != 0) mlog("Open packet : Data mistmach\r\n");

		//test of collect
		for (int i = 0; i < result_size; i++)
			danish_yiq(result[i]);

		fret = danish_parse(&params);
		if (fret) {
		
		} else {
			mlog("Parse error!\r\n");
		}

		free(data);
		free(result);

		if (error) {
			printf("Test %d Failed\r\n", i + 1);
			failed_cntr++;
		} else {
			succ_cntr++;
		}
	}

	printf("Tests : %d\r\n", Test_iter);
	printf("Failed : %d\r\nSuccessfull : %d\r\n", failed_cntr, succ_cntr);

	printf("Stats:\r\n");
	printf("\tSuccessfull received : %d\r\n", danish_stats_get_successfull_received());
	printf("\tChecksum error : %d\r\n", danish_stats_get_checksum_error());
	printf("\tFull error : %d\r\n", danish_stats_get_full_error());

	return 1;
}
