#include <danish.h>

#ifdef DANISH_STATS
uint32_t danish_stats_full_err = 0;
uint32_t danish_stats_timeout = 0;
uint32_t danish_stats_checksum_err = 0;
uint32_t danish_stats_rcv = 0;
#endif

static uint8_t danish_rx_buffer[DANISH_MAX_PACKET_SIZE + 10];
static uint8_t danish_rx_cntr = 0;
static uint64_t rx_timestamp;

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
	packet[cntr++] = checksum;
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

	result->function = packet[PACKET_FUNCTION];
	result->address = packet[PACKET_ADDRESS];
	result->regID = (packet[PACKET_REG_ID_MSB] << 8) + (packet[PACKET_REG_ID_LSB]);
	result->len = packet[PACKET_LEN];
	result->data = &packet[PACKET_DATA];
	return 1;
#endif
}


void danish_yiq(uint8_t c) {
	rx_timestamp = get_timestamp();
	danish_rx_buffer[danish_rx_cntr++] = c;
	if (danish_rx_cntr >= DANISH_MAX_PACKET_SIZE) {
		danish_rx_cntr = 0;
#ifdef DANISH_STATS
		danish_stats_full_err++;
#endif
	}
}

int danish_parse(danish_st *packet) {
	if (delay_ms(rx_timestamp, 1)) {
#ifdef DANISH_STATS
		if (danish_rx_cntr > 0)
			danish_stats_timeout++;
#endif
		danish_rx_cntr = 0;
	}

	if (danish_rx_cntr >= 7) {
		int fret = danish_ach(danish_rx_buffer, danish_rx_cntr, packet);
		if (fret == -1) {
			//checksum error
#ifdef DANISH_STATS
			danish_stats_checksum_err++;
#endif
			danish_rx_cntr = 0;
		} else if (fret == 1) {
#ifdef DANISH_STATS
			danish_stats_rcv++;
#endif
			danish_rx_cntr = 0;
			return 1;
		}
	}
	return 0;
}

#ifdef DANISH_STATS
uint32_t danish_stats_get_successfull_received() {
	return danish_stats_rcv;
}

uint32_t danish_stats_get_checksum_error() {
	return danish_stats_checksum_err;
}

uint32_t danish_stats_get_full_error() {
	return danish_stats_full_err;
}
#endif
