/*
 * fsm.c
 *
 *  Created on: Apr 22, 2022
 *      Author: Zeinab
 */

#include <fsm.h>
#include <assert.h>

static sfsm *machines = NULL;

sfsm *make_fsm(void (*machine)(struct fsm_st* fsm))
{
	sfsm *fsm = (struct fsm_st *)malloc(sizeof(struct fsm_st));

	assert(fsm != NULL);

	memset((uint8_t *)fsm , 0, sizeof(sfsm));

	if (machines == NULL)
		machines = fsm;
	else {
		sfsm *fsm_ptr = machines;
		while (fsm_ptr->next != NULL)
			fsm_ptr = fsm_ptr->next;

		fsm_ptr->next = fsm;
	}

	fsm->machine = machine;
	fsm->status = FSM_RUN;

	return fsm;
}

void fsm_signal(signal_enu signal) {
	sfsm *fsm = machines;
	while (fsm != NULL) {
		if (fsm->signals & signal) {
			fsm->signal_flags |= signal;
		}
		fsm = fsm->next;
	}
}

uint8_t fsm_signal_ready(sfsm *fsm, signal_enu signal) {
	if (fsm->signal_flags & signal) {
		fsm->signal_flags &= ~signal;
		return 1;
	}
	return 0;
}

void fsm_signal_register(sfsm *fsm, signal_enu signal) {
	fsm->signals |= signal;
}
void fsm_signal_unregister(sfsm *fsm, signal_enu signal) {
	fsm->signals &= ~signal;
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
	machines = NULL;
}

void fsm_manager()
{
	sfsm *fsms = machines;

	while (fsms != NULL) {
		if (fsms->status == FSM_DELAY) {
			if (delay_ms(fsms->timestamp, fsms->delay))
			{
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
			if (fsms->signal_flags & fsms->block_template) {
				fsms->status = FSM_RUN;
			}
		}
		fsms = fsms->next;
	}
}

void fsm_wait_for_signal(sfsm *fsm, signal_enu signal, uint16_t step) {
	fsm->status = FSM_BLOCK_FOR_SIGNAL;
	fsm->block_template = signal;
	fsm->step = step;
}
