/*
 * delay.c
 *
 *  Created on: Apr 22, 2022
 *      Author: Amin Aghakhani
 */
#include <delay.h>


#ifndef MY_DELAY
uint64_t get_timestamp() {
	return system_tick_cntr;
}
#endif

uint8_t delay_ms(uint64_t timestamp, uint32_t delay)
{
	if ((get_timestamp() - timestamp) >= delay)
		return 1;

	return 0;
}

uint8_t delay_s(uint64_t timestamp, uint32_t delay) {
	return delay_ms(timestamp, delay * 1000);
}

void wait_s(uint32_t delay) {
	volatile uint64_t ts = get_timestamp();
	delay = delay * 1000;
	while (!delay_ms(ts, delay));
}

void wait_ms(uint32_t delay) {
	volatile uint64_t ts = get_timestamp();
	while (!delay_ms(ts, delay));
}
