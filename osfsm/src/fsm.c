/*
 * fsm.c
 *
 *  Created on: Nov 23, 2021
 *      Author: Amin Aghakhani
 */

#include <fsm.h>

static fsm_st _v_machines_[FSM_MAX_AVAL];
static uint8_t _v_machine_cntr_ = 0;

int8_t fsm_add(void (*_fsm)(uint8_t _mid, uint8_t *_state)) {
	if (_v_machine_cntr_ >= FSM_MAX_AVAL) return -1;

	_v_machines_[_v_machine_cntr_].fsm = _fsm;
	_v_machines_[_v_machine_cntr_].state = 0;
	_v_machines_[_v_machine_cntr_].mode = FSM_MODE_RUN;
	_v_machine_cntr_++;
	return _v_machine_cntr_ - 1;
}

void fsm_delay(uint8_t _mid, uint32_t _delay) {
	_v_machines_[_mid].timestamp = get_timestamp();
	_v_machines_[_mid].delay = _delay;
	_v_machines_[_mid].mode = FSM_MODE_DELAY;
}

void fsm_wait(uint8_t _mid, ret_enu (*_waitCallback)(void)) {
	_v_machines_[_mid].mode = FSM_MODE_WAIT;
	_v_machines_[_mid].waitCallback = _waitCallback;
}

void fsm_semWait(uint8_t _mid, sem_enu _sem) {
	if (sem_busy(_sem) == RET_FALSE) {
		sem(_sem);
	} else {
		_v_machines_[_mid].mode = FSM_MODE_SEM_WAIT;
	}
	_v_machines_[_mid].semaphore = _sem;
}

void fsm_init() {
	sem_init();
	_v_machine_cntr_ = 0;
}

void fsm_manager() {
	fsm_st *fsm_ptr;
	for (int i = 0; i < _v_machine_cntr_; i++) {
		fsm_ptr = &_v_machines_[i];

		if (fsm_ptr->mode == FSM_MODE_DELAY) {
			if (delay_ms(fsm_ptr->timestamp, fsm_ptr->delay)) {
				fsm_ptr->mode = FSM_MODE_RUN;
			}
		} else if (fsm_ptr->mode == FSM_MODE_RUN) {
			fsm_ptr->fsm(i, &fsm_ptr->state);
		} else if (fsm_ptr->mode == FSM_MODE_WAIT) {
			if (fsm_ptr->waitCallback() == RET_TRUE) {
				fsm_ptr->mode = FSM_MODE_RUN;
			}
		} else if (fsm_ptr->mode == FSM_MODE_SEM_WAIT) {
			if (sem_busy(fsm_ptr->semaphore) != RET_BUSY) {
				sem(fsm_ptr->semaphore);
				fsm_ptr->mode = FSM_MODE_RUN;
			}
		}
	}
}



