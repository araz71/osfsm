/*
 * delay.c
 *
 *  Created on: Nov 23, 2021
 *      Author: Amin Aghakhani
 */

#include <delay.h>

uint64_t get_timestamp() {
	return SysTickCntr;
}
uint8_t delay_ms(uint64_t _ts, uint32_t _delay) {
	if ((SysTickCntr - _ts) >= _delay) return 1;
	return 0;
}

