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

#define FSM_AUTO_STEP
#define FSM_BREAK		return
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

void fsm_delay(struct fsm_st *fsm, uint32_t delay, uint8_t step);
void fsm_wait(struct fsm_st *fsm, uint8_t (*wait_callback)(void), uint32_t delay, uint8_t step);

uint8_t fsm_check_delay(struct fsm_st *fsm, uint32_t delay);
void fsm_make_time_point(struct fsm_st *fsm);

void fsm_manager();
void fsm_init();
