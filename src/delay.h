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

/*
 * Waits for seconds
 *
 * @param delay Delay in seconds type
 */
void wait_s(uint32_t delay);

/*
 * Waits for mseconds
 *
 * @param delay Delay in mseconds
 */
void wait_ms(uint32_t delay);

/*
 * Checks if requested point is reached to stored timestamp
 *
 * @param timestamp Time pointed value
 * @param delay Number of points after timestamp in mseconds
 *
 * @return 1 if delay is reached or passed. otherwise 0
 */
uint8_t delay_ms(uint64_t timestamp, uint32_t delay);

uint8_t delay_s(uint64_t timestamp, uint32_t delay);

#ifdef MY_DELAY
extern uint64_t get_timestamp();
#else
uint64_t get_timestamp();
#endif

#endif /* DELAY_H_ */
