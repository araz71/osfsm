/*
 * fsm.c
 *
 *  Created on: Apr 22, 2022
 *      Author: Zeinab
 */

#include <fsm.h>

static struct fsm_st *machines = NULL;

struct fsm_st *make_fsm(void (*machine)(struct fsm_st* fsm))
{
	struct fsm_st *fsm = (struct fsm_st *)malloc(sizeof(struct fsm_st));

	if (fsm == NULL) return NULL;
	memset((uint8_t *)fsm , 0, sizeof(struct fsm_st));

	if (machines == NULL)
		machines = fsm;
	else {
		struct fsm_st *fsm_ptr = machines;
		while (fsm_ptr->next != NULL)
			fsm_ptr = fsm_ptr->next;

		fsm_ptr->next = fsm;
	}

	fsm->machine = machine;
	fsm->status = FSM_RUN;

	return fsm;
}

void fsm_delay(struct fsm_st *fsm, uint32_t delay, uint8_t step)
{
	fsm->status = FSM_DELAY;
	fsm->timestamp = get_timestamp();
	fsm->delay = delay;
	fsm->step += step;
}

void fsm_wait(struct fsm_st *fsm, uint8_t (*wait_callback)(void), uint32_t delay, uint8_t step)
{
	fsm->delay = delay;
	fsm->flag_callback = wait_callback;
	fsm->status = FSM_WAIT;
	fsm->timestamp = get_timestamp();
	fsm->step += step;
}

uint8_t fsm_check_delay(struct fsm_st *fsm, uint32_t delay) {
	return (delay_ms(fsm->timestamp, delay));
}

void fsm_make_time_point(struct fsm_st *fsm) {
	fsm->timestamp = get_timestamp();
}

void fsm_init() {
	machines = NULL;
	delay_init();
}

void fsm_manager()
{
	struct fsm_st *fsms = machines;

	while (fsms != NULL) {
		if (fsms->status == FSM_DELAY){
			if (delay_ms(fsms->timestamp, fsms->delay))
				fsms->timestamp = get_timestamp();
				fsms->status = FSM_RUN;
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
