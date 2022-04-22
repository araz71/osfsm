/*
 * delay.h
 *
 *  Created on: Apr 22, 2022
 *      Author: Zeinab
 */

#ifndef DELAY_H_
#define DELAY_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint64_t tick_cntr;

#define get_timestamp()		tick_cntr
uint8_t delay_ms(uint64_t timestamp, uint32_t delay);

#endif /* DELAY_H_ */
