/*
 * io_scanner.h
 *
 *  Created on: Jul 28, 2022
 *      Author: Duman
 */

#ifndef IO_SCANNER_H_
#define IO_SCANNER_H_

#include <def.h>
#include <delay.h>

#ifdef IO_SCANNER_MAX_AVAL

void io_scanner_add(GPIO_TypeDef* port, uint8_t pin, uint8_t trig_is_high,
		void (*trig_callback)(void), void (*untrig_callback)(void));

void io_scanner();

#endif

#endif /* IO_SCANNER_H_ */
