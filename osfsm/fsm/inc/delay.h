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

#ifndef MY_DELAY
uint64_t system_tick_cntr;
#define get_timestamp()	system_tick_cntr
#endif

void wait_s(uint32_t delay);
void wait_ms(uint32_t delay);
uint8_t delay_ms(uint64_t timestamp, uint32_t delay);
uint8_t delay_s(uint64_t timestamp, uint32_t delay);
void delay_init();
#endif /* DELAY_H_ */
