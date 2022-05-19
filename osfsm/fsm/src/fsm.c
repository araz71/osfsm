/*
 * fsm.c
 *
 *  Created on: Apr 22, 2022
 *      Author: Zeinab
 */

#include <fsm.h>

static sfsm *machines = NULL;

sfsm *make_fsm(void (*machine)(struct fsm_st* fsm))
{
	sfsm *fsm = (struct fsm_st *)malloc(sizeof(struct fsm_st));

	if (fsm == NULL) return NULL;
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
		}
		fsms = fsms->next;
	}
}
