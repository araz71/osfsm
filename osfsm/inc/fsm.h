/*
 * fsm.h
 *
 *  Created on: Nov 23, 2021
 *      Author: Amin Aghakhani
 */

#ifndef FSM_H_
#define FSM_H_

#include <stdint.h>
#include <delay.h>

#define FSM_MAX_AVAL		10
typedef enum {
	FSM_MODE_RUN,
	FSM_MODE_DELAY,
	FSM_MODE_WAIT,
	FSM_MODE_FIN,
} fsm_mode_enu;

typedef enum {
	RET_FALSE,
	RET_TRUE,

	RET_BUSY = 255,
} ret_enu;

typedef struct {
	void (*fsm)(uint8_t _mid, uint8_t *_state);
	uint8_t state;
	fsm_mode_enu mode;

	uint64_t timestamp;
	uint32_t delay;
	ret_enu (*waitCallback)(void);
} fsm_st;


int8_t fsm_add(void (*_fsm)(uint8_t _mid, uint8_t *_state));
void fsm_delay(uint8_t _mid, uint32_t _delay);
void fsm_wait(uint8_t _mid, ret_enu (*_waitCallback)(void));

void fsm_manager();

#define DELAY(MS)			fsm_delay(_mid, MS)

#endif /* FSM_H_ */
