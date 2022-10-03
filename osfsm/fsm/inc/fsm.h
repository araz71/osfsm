/*
 * fsm.h
 *
 *  Created on: Apr 22, 2022
 *      Author: Zeinab
 */
#ifndef _H_FSM_H
#define _H_FSM_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <delay.h>

#define FSM_AVAL				12
#define TIMER_AVAL				10
#define TIMER_UNINIT_VALUE		0xFF

#define FSM_AUTO_STEP
#define FSM_BREAK				return
#define FSM_CURRENT_STEP		fsm->step
#define FSM_NEXT_STEP			fsm->step + 1
#define FSM_GO_NEXT				fsm->step++

#define SIGNAL_READY(SIGNAL)	fsm_signal_ready(fsm, SIGNAL)
#define SIGNAL_REG(SIGNAL)		fsm_signal_register(fsm, SIGNAL)
#define SIGNAL_UNREG(SIGNAL)	fsm_signal_unregister(fsm, SIGNAL)
#define SIGNAL_CLEAR(SIGNAL)	fsm->signal_flags &= ~SIGNAL

typedef enum
{
	FSM_STOP,
	FSM_RUN,
	FSM_DELAY,
	FSM_WAIT,
	FSM_WAIT_FOR_MUTEX,
	FSM_BLOCK_FOR_SIGNAL,
	FSM_SLEEP,
} fsm_status_enu;

typedef enum {
	SIGNAL_EXIT		= 0x01,
	SIGNAL_SLEEP	= 0x02,
	SIGNAL_USR_1	= 0x04,
	SIGNAL_USR_2	= 0x08,
	SIGNAL_USR_3	= 0x10,
	SIGNAL_USR_4	= 0x20,
	SIGNAL_USR_5	= 0x40,
} signal_enu;

typedef enum {
	FSM_MUTEX_1		= 0x0001,
	FSM_MUTEX_2		= 0x0002,
	FSM_MUTEX_3		= 0x0004,
	FSM_MUTEX_4		= 0x0008,
	FSM_MUTEX_5		= 0x0010,
	FSM_MUTEX_6		= 0x0020,
	FSM_MUTEX_7		= 0x0040,
	FSM_MUTEX_8		= 0x0080,
	FSM_MUTEX_9		= 0x0100,
	FSM_MUTEX_10	= 0x0200,
	FSM_MUTEX_11	= 0x0400,
	FSM_MUTEX_12	= 0x0800,
	FSM_MUTEX_13	= 0x1000,
	FSM_MUTEX_14	= 0x2000,
	FSM_MUTEX_15	= 0x4000,
	FSM_MUTEX_16	= 0x8000,
} fsm_mutex_enu;

typedef enum {
	TIMER_STOP,
	TIMER_RUN,
} timer_state_enu;

#pragma pack(push)
#pragma pack(1)

struct fsm_st
{
	void (*machine)(struct fsm_st* fsm);

	fsm_status_enu status;
	uint16_t step;

	uint64_t timestamp;
	uint32_t delay;

	uint8_t signals;

	uint16_t mutex;

	uint8_t block_template;

	uint8_t (*flag_callback)(void);
};

typedef struct {
	void (*callback)(void);

	uint32_t delay;
	uint64_t timestamp;
	timer_state_enu state;
} stimer;
#pragma pack(pop)

typedef struct fsm_st sfsm;

void fsm_mutex_lock(sfsm* fsm, fsm_mutex_enu mutex);
void fsm_mutex_unlock(sfsm* fsm, fsm_mutex_enu mutex);
uint8_t fsm_mutex_check(fsm_mutex_enu mutex);

void mutex_lock(fsm_mutex_enu mutex);
void mutex_unlock(fsm_mutex_enu mutex);
uint8_t mutex_busy(fsm_mutex_enu mutex);

struct fsm_st *make_fsm(void (*machine)(struct fsm_st* fsm));
void fsm_stop(struct fsm_st* fsm);

void fsm_delay(struct fsm_st *fsm, uint32_t delay);
void fsm_delay_jump(sfsm *fsm, uint32_t delay, uint16_t step);

void fsm_wait(struct fsm_st *fsm, uint8_t (*wait_callback)(void), uint32_t delay);
void fsm_wait_jump(sfsm *fsm, uint8_t (*wait_callback)(void), uint32_t delay, uint16_t step);

void fsm_signal(signal_enu signal);
void fsm_wait_for_signal(sfsm *fsm, signal_enu signal, uint16_t step);

void fsm_sleep(sfsm *fsm);

uint8_t fsm_check_delay(struct fsm_st *fsm, uint32_t delay);
void fsm_make_time_point(struct fsm_st *fsm);

void fsm_manager();
void fsm_init();

uint8_t fsm_make_timer(uint32_t delay, void (*callback)(void));
void fsm_timer_stop(uint8_t* timer);
void fsm_timer_restart(uint8_t timer);

#endif
