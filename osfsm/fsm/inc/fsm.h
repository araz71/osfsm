/*
 * fsm.h
 *
 *  Created on: Apr 22, 2022
 *      Author: Zeinab
 */


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <delay.h>

typedef enum
{
	FSM_RUN,
	FSM_DELAY,
	FSM_WAIT,
} fsm_status_enu;

struct fsm_st
{
	void (*machine)(struct fsm_st* fsm);

	struct fsm_st *next;

	fsm_status_enu status;
	uint16_t step;

	uint64_t timestamp;
	uint32_t delay;

	uint8_t (*flag_callback)(void);
};

struct fsm_st *make_fsm(void (*machine)(struct fsm_st* fsm));
void fsm_stop(struct fsm_st* fsm);

void fsm_delay(struct fsm_st *fsm, uint32_t delay);
void fsm_wait(struct fsm_st *fsm, uint8_t (*wait_callback)(void), uint32_t delay);

void fsm_manager();
