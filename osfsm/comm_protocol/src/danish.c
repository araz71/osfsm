#include <danish.h>

uint8_t danish_make(uint8_t address, function_enu function, uint16_t regID, uint8_t len, uint8_t *data, uint8_t *packet) {
	uint8_t cntr = 0;
	uint16_t checksum = 0;
	
	if (len > DANISH_MAX_DATA_SIZE)
		return 0;

	packet[cntr++] = address;
	packet[cntr++] = function;
	packet[cntr++] = regID >> 8;
	packet[cntr++] = regID;
	packet[cntr++] = len;

	for (uint8_t i = 0; i < len; i++)
		packet[cntr++] = data[i];

#ifdef DANISH_CHECKSUM_CRC

#else
	for (uint8_t i = 0; i < cntr; i++)
		checksum += packet[i];

	packet[cntr++] = checksum >> 8;
	packet[cntr] = checksum;
#endif
	return cntr;
}

int8_t danish_ach(uint8_t *packet, uint8_t len, danish_st *result) {
	//summation of  address, function, register, len and checksum sizes
	if (len < 7) return 0;
	if (len < (7 + packet[PACKET_LEN])) return 0;
	if (len > DANISH_MAX_PACKET_SIZE) return -1;
	if (packet[PACKET_LEN] > DANISH_MAX_DATA_SIZE) return -1;

	uint16_t checksum = 0;
	uint16_t received_checksum = (packet[len - 2] << 8) + (packet[len - 1]); 
#ifdef DANISH_CHECKSUM_CRC

#else
	for (uint8_t i = 0; i < len - 2; i++)
		checksum += packet[i];

	if (checksum != received_checksum) return -1;

	result->address = packet[PACKET_ADDRESS];
	result->regID = (packet[PACKET_REG_ID_MSB] << 8) + (packet[PACKET_REG_ID_LSB]);
	result->len = packet[PACKET_LEN];
	memcpy(result->data, &packet[PACKET_DATA], result->len);
	return 1;
#endif
}
