/*
 * delay.h
 *
 *  Created on: Nov 23, 2021
 *      Author: Amin Aghakhani
 */

#ifndef DELAY_H_
#define DELAY_H_

#include <stdint.h>

uint64_t SysTickCntr;

uint64_t get_timestamp();
uint8_t delay_ms(uint64_t _ts, uint32_t _delay);


#endif /* DELAY_H_ */
