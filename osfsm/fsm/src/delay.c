/*
 * delay.c
 *
 *  Created on: Apr 22, 2022
 *      Author: Zeinab
 */

#include <delay.h>

uint8_t delay_ms(uint64_t timestamp, uint32_t delay)
{
	if ((get_timestamp() - timestamp) >= delay)
		return 1;

	return 0;
}

void wait_s(uint32_t delay) {
	uint64_t ts = get_timestamp();
	delay = delay * 1000;
	while (!delay_ms(ts, delay));
}

void wait_ms(uint32_t delay) {
	uint64_t ts = get_timestamp();
	while (!delay_ms(ts, delay));
}
