/*
 * fsm.c
 *
 *  Created on: Apr 22, 2022
 *      Author: Zeinab
 */

#include <fsm.h>
#include <assert.h>

static sfsm machines[FSM_AVAL];
static stimer timers[TIMER_AVAL];
static uint16_t fsm_mutex = 0;

void mutex_lock(fsm_mutex_enu mutex) {
	fsm_mutex |= mutex;
}
void mutex_unlock(fsm_mutex_enu mutex) {
	fsm_mutex &= ~mutex;
}
uint8_t mutex_busy(fsm_mutex_enu mutex) {
	if (fsm_mutex & mutex) return 1;
	return 0;
}

uint8_t fsm_mutex_check(fsm_mutex_enu mutex) {
	if (!(fsm_mutex & mutex)) return 1;
	return 0;
}

void fsm_mutex_lock(sfsm* fsm, fsm_mutex_enu mutex) {
	if (fsm_mutex & mutex) {
		fsm->status = FSM_WAIT_FOR_MUTEX;
		fsm->mutex |= mutex;
	} else {
		fsm_mutex |= mutex;
	}
}

void fsm_mutex_unlock(sfsm* fsm, fsm_mutex_enu mutex) {
	fsm_mutex &= ~mutex;
	fsm->mutex &= ~mutex;
}

sfsm *make_fsm(void (*machine)(struct fsm_st* fsm))
{
	sfsm *fsm = NULL;

	for (int i = 0; i < FSM_AVAL; i++) {
		if (machines[i].status == FSM_STOP) {
			fsm = &machines[i];
			break;
		}
	}
	if (fsm == NULL) {
		printf("No space avaliable to mke fsm\r\n");
		assert(0);
	}

	memset((uint8_t *)fsm , 0, sizeof(sfsm));

	fsm->machine = machine;
	fsm->status = FSM_RUN;

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

uint8_t fsm_check_delay(sfsm *fsm, uint32_t delay) {
	return (delay_ms(fsm->timestamp, delay));
}

void fsm_make_time_point(sfsm *fsm) {
	fsm->timestamp = get_timestamp();
}

void fsm_init() {
	for (int i = 0; i < FSM_AVAL; i++) {
		memset((uint8_t *)&machines[i], 0, sizeof(sfsm));
	}
}

void fsm_manager()
{
	sfsm *fsms = NULL;

	for (int i = 0; i < FSM_AVAL; i++) {
		fsms = &machines[i];
		if (fsms->status == FSM_STOP) continue;

		if (fsms->status == FSM_DELAY) {
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

		} else if (fsms->status == FSM_RUN) {
			fsms->machine(fsms);

		} else if (fsms->status == FSM_BLOCK_FOR_SIGNAL) {
			if (fsms->signal_flags == 0) {
				fsms->timestamp = get_timestamp();
				fsms->status = FSM_RUN;
			}

		} else if (fsms->status == FSM_WAIT_FOR_MUTEX) {
			if ((fsms->mutex & fsm_mutex) == 0) {
				fsms->status = FSM_RUN;
				fsm_mutex |= fsms->mutex;
				fsms->mutex = 0;
			}
		}
	}

	for (int i = 0; i < TIMER_AVAL; i++) {
		if (timers[i].state == TIMER_RUN) {
			if (delay_ms(timers[i].timestamp, timers[i].delay)) {
				timers[i].state = TIMER_STOP;
				timers[i].callback();
			}
		}
	}
}

void fsm_wait_for_signal(sfsm *fsm, signal_enu signal, uint16_t step) {
	fsm->status = FSM_BLOCK_FOR_SIGNAL;
	fsm->signals |= signal;
	fsm->step = step;
}

void fsm_signal(signal_enu signal) {
	sfsm *fsm = machines;
	for (int i = 0; i < FSM_AVAL; i++) {
		fsm = &machines[i];
		if (fsm->signals & signal)
			fsm->signal_flags &= ~signal;
	}
}

uint8_t fsm_make_timer(uint32_t delay, void (*callback)(void)) {
	uint8_t timer_aval = TIMER_UNINIT_VALUE;
	for (uint8_t i = 0; i < TIMER_AVAL; i++) {
		if (timers[i].state == TIMER_STOP) {
			timer_aval = i;
			break;
		}
	}
	if (timer_aval == TIMER_UNINIT_VALUE) return TIMER_UNINIT_VALUE;
	timers[timer_aval].timestamp = get_timestamp();
	timers[timer_aval].state = TIMER_RUN;
	timers[timer_aval].callback = callback;
	timers[timer_aval].delay = delay;
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


