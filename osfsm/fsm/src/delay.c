/*
 * delay.c
 *
 *  Created on: Apr 22, 2022
 *      Author: Zeinab
 */

#include <delay.h>

void delay_init() {
	tick_cntr = 0;
}

uint8_t delay_ms(uint64_t timestamp, uint32_t delay)
{
	if ((get_timestamp() - timestamp) >= delay)
		return 1;

	return 0;
}
