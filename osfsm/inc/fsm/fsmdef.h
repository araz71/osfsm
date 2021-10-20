/*
 * fsmdef.h
 *
 *  Created on: Oct 20, 2021
 *      Author: Duman
 */

#ifndef FSMDEF_H_
#define FSMDEF_H_

#include <stdint.h>

uint64_t SysTickCntr;

#define FSM_UNDEF			0xFF
#define FSM_MAX_AVAL		10
#define get_timestamp()		SysTickCntr
typedef uint8_t fsmID;

uint8_t delay_ms(uint64_t _ts, uint32_t _delay);

#endif /* FSMDEF_H_ */
