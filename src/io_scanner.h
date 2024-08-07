/*
 * io_scanner.h
 *
 *  Created on: Jul 28, 2022
 *      Author: Duman
 */

#ifndef IO_SCANNER_H_
#define IO_SCANNER_H_

#include <fsm_def.h>

#ifdef IO_SCANNER_MAX_AVAL

#include <def.h>
#include <delay.h>

void io_scanner_add(uint8_t (*reader_callback)(void), uint8_t trig_is_high,
		void (*trig_callback)(void), void (*untrig_callback)(void));

void io_scanner();

#endif

#endif /* IO_SCANNER_H_ */
