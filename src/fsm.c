/*
 * fsm.c
 *
 *  Created on: Apr 22, 2022
 *      Author: Amin Aghakhani
 */

#include "fsm.h"
#include <log.h>
#include <assert.h>

static sfsm machines[FSM_AVAL];
static stimer timers[TIMER_AVAL];

#ifdef FSM_SUPPORT_MUTEX
static uint16_t fsm_mutex = 0;

void mutex_lock(fsm_mutex_enu mutex) {
#ifdef DEBUG_MUTEX
	mlog("Mutex %d locked", mutex);
#endif
	fsm_mutex |= mutex;
}

void mutex_unlock(fsm_mutex_enu mutex) {
#ifdef DEBUG_MUTEX
	mlog("Mutex %d unlocked", mutex);
#endif
	fsm_mutex &= ~mutex;
}

uint8_t mutex_busy(fsm_mutex_enu mutex) {
	if (fsm_mutex & mutex)
		return 1;

	return 0;
}

uint8_t fsm_mutex_check(fsm_mutex_enu mutex) {
	if (!(fsm_mutex & mutex))
		return 1;

	return 0;
}

void fsm_mutex_lock(sfsm* fsm, fsm_mutex_enu mutex) {
	if (fsm_mutex & mutex) {
#ifdef DEBUG_MUTEX
		mlog("FSM[%s] waits for mutex[%d]", fsm->machine_name, mutex);
#endif
		fsm->status = FSM_WAIT_FOR_MUTEX;
		fsm->mutex |= mutex;
	} else {
#ifdef DEBUG_MUTEX
		mlog("Mutex[%d] locked for FSM[%s]", mutex, fsm->machine_name);
#endif
		fsm_mutex |= mutex;
	}
}

void fsm_mutex_unlock(sfsm* fsm, fsm_mutex_enu mutex) {
#ifdef DEBUG_MUTEX
	mlog("Mutex[%d] unlocked by FSM[%s]", mutex, fsm->machine_name);
#endif
	fsm_mutex &= ~mutex;
	fsm->mutex &= ~mutex;
}
#endif

sfsm* make_fsm_with_name(void (*machine)(sfsm* fsm), const char* name) {
	sfsm* this_fsm = make_fsm(machine);
#ifdef DEBUG
	this_fsm->machine_name = (char*) name;
	mlog("Machine[%s] added", name);
#endif

	return this_fsm;
}

sfsm *make_fsm(void (*machine)(struct fsm_st* fsm)) {
	sfsm *fsm = NULL;

	for (int i = 0; i < FSM_AVAL; i++) {
		if (machines[i].status == FSM_STOP) {
			fsm = &machines[i];
			break;
		}
	}

	if (fsm == NULL)
		assert(0);

	memset((uint8_t *)fsm , 0, sizeof(sfsm));

	fsm->machine = machine;
	fsm->status = FSM_RUN;

#ifdef DEBUG
	fsm->machine_name = (char *)__FUNCTION__;
#endif

	return fsm;
}

void fsm_sleep(sfsm *fsm) {
	fsm->status = FSM_SLEEP;
}

void fsm_delay(sfsm *fsm, uint32_t delay)
{
	fsm->status = FSM_DELAY;
	fsm->timestamp = get_timestamp();
	fsm->delay = delay;
}

void fsm_delay_jump(sfsm *fsm, uint32_t delay, uint16_t step)
{
	fsm_delay(fsm, delay);
	fsm->step = step;
}

void fsm_wait_jump(sfsm *fsm, uint8_t (*wait_callback)(void), uint32_t delay, uint16_t step)
{
	fsm_wait(fsm, wait_callback, delay);
	fsm->step = step;
}

void fsm_wait(sfsm *fsm, uint8_t (*wait_callback)(void), uint32_t delay)
{
	fsm->delay = delay;
	fsm->flag_callback = wait_callback;
	fsm->status = FSM_WAIT;
	fsm->timestamp = get_timestamp();
}

uint8_t fsm_check_delay(sfsm *fsm, uint32_t ms) {
	return (delay_ms(fsm->timestamp, ms));
}

void fsm_make_time_point(sfsm *fsm) {
	fsm->timestamp = get_timestamp();
}

void fsm_init() {
	for (int i = 0; i < FSM_AVAL; i++)
		memset((uint8_t *)&machines[i], 0, sizeof(sfsm));
}

void fsm_manager()
{
	sfsm *fsms = NULL;

	for (int i = 0; i < FSM_AVAL; i++) {
		fsms = &machines[i];

		if (fsms->status == FSM_STOP)
			continue;

		else if (fsms->status == FSM_DELAY) {
			if (delay_ms(fsms->timestamp, fsms->delay)) {
				fsms->timestamp = get_timestamp();
				fsms->status = FSM_RUN;
			}

		} else if (fsms->status == FSM_WAIT) {
			if (fsms->flag_callback() ||
					(fsms->delay != 0 && delay_ms(fsms->timestamp, fsms->delay)))
			{
				fsms->timestamp = get_timestamp();
				fsms->status = FSM_RUN;
			}

		} else if (fsms->status == FSM_RUN)
			fsms->machine(fsms);

#ifdef FSM_SUPPORT_SIGNAL
		else if (fsms->status == FSM_BLOCK_FOR_SIGNAL) {
			if (fsms->signals == 0) {
				fsms->timestamp = get_timestamp();
				fsms->status = FSM_RUN;
			}
		}
#endif

#ifdef FSM_SUPPORT_MUTEX
		else if (fsms->status == FSM_WAIT_FOR_MUTEX) {
			if ((fsms->mutex & fsm_mutex) == 0) {
				fsms->status = FSM_RUN;
				fsm_mutex |= fsms->mutex;
				fsms->mutex = 0;
			}
		}
#endif
	}

	for (int i = 0; i < TIMER_AVAL; i++) {
		if (timers[i].state == TIMER_RUN) {
			if (delay_ms(timers[i].timestamp, timers[i].delay)) {
				timers[i].state = TIMER_STOP;
				timers[i].callback(timers[i].arg);
			}
		}
	}
}

#ifdef FSM_SUPPORT_SIGNAL
void fsm_wait_for_signal(sfsm *fsm, signal_enu signal, uint16_t step) {
	fsm->status = FSM_BLOCK_FOR_SIGNAL;
	fsm->signals |= signal;
	fsm->step = step;

	mlog("FSM[%s] sleeped for signal[%d]", fsm->machine_name, signal);
}

void fsm_signal(signal_enu signal) {
	sfsm *fsm;
	for (int i = 0; i < FSM_AVAL; i++) {
		fsm = &machines[i];
		if (fsm->signals & signal) {
			fsm->signals &= ~signal;
			mlog("Send signal[%d] to FSM[%s]", signal, fsm->machine_name);
		}
	}
}
#endif

uint8_t fsm_make_timer(uint32_t delay, void (*callback)(uint32_t arg), uint32_t arg) {
	uint8_t timer_aval = TIMER_UNINIT_VALUE;
	for (uint8_t i = 0; i < TIMER_AVAL; i++) {
		if (timers[i].state == TIMER_STOP) {
			timer_aval = i;
			break;
		}
	}

	if (timer_aval == TIMER_UNINIT_VALUE)
		return TIMER_UNINIT_VALUE;

	timers[timer_aval].timestamp = get_timestamp();
	timers[timer_aval].state = TIMER_RUN;
	timers[timer_aval].callback = callback;
	timers[timer_aval].delay = delay;
	timers[timer_aval].arg = arg;

	return timer_aval;
}

void fsm_timer_stop(uint8_t* timer) {
	if ((*timer) != TIMER_UNINIT_VALUE) {
		if ((*timer) < TIMER_AVAL)
			timers[*timer].state = TIMER_STOP;

		*timer = TIMER_UNINIT_VALUE;
	}
}

void fsm_timer_restart(uint8_t timer) {
	if (timer != TIMER_UNINIT_VALUE && timer < TIMER_AVAL)
		timers[timer].timestamp = get_timestamp();
}


