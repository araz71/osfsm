/*
 * delay.c
 *
 *  Created on: Apr 22, 2022
 *      Author: Amin Aghakhani
 */
#include <delay.h>


extern uint64_t system_tick_cntr;

uint64_t __attribute__((weak))  get_timestamp() {
	return system_tick_cntr;
}


uint8_t delay_ms(uint64_t timestamp, uint32_t delay) {
	if ((get_timestamp() - timestamp) >= delay)
		return 1;

	return 0;
}

uint8_t delay_s(uint64_t timestamp, uint32_t delay) {
	return delay_ms(timestamp, delay * 1000);
}

uint8_t delay_m(uint64_t timestamp, uint32_t delay) {
	return delay_s(timestamp, delay * 60);
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
