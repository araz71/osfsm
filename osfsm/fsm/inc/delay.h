/*
 * delay.h
 *
 *  Created on: Apr 22, 2022
 *      Author: Amin Aghakhani
 */
#ifndef DELAY_H_
#define DELAY_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifndef MY_DELAY
uint64_t system_tick_cntr;
#endif

void wait_s(uint32_t delay);
void wait_ms(uint32_t delay);
uint8_t delay_ms(uint64_t timestamp, uint32_t delay);
uint8_t delay_s(uint64_t timestamp, uint32_t delay);
void delay_init();

#ifdef MY_DELAY
extern uint64_t get_timestamp();
#else
uint64_t get_timestamp();
#endif

#endif /* DELAY_H_ */
