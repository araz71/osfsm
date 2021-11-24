/*
 * sem.c
 *
 *  Created on: Nov 23, 2021
 *      Author: Zeinab
 */

#include <sem.h>

static uint8_t _v_sem_[_SEM_MAX_];

ret_enu sem(sem_enu _sem) {
	if (_sem >= _SEM_MAX_) return RET_FALSE;

	if (_v_sem_[_sem] != 0) {
		return RET_FALSE;
	}
	_v_sem_[_sem] = 1;
	return RET_TRUE;
}

ret_enu sem_busy(sem_enu _sem) {
	if (_v_sem_[_sem] == 0) return RET_FALSE;
	return RET_BUSY;
}

void sem_free(sem_enu _sem) {
	if (_sem >= _SEM_MAX_) return;
	_v_sem_[_sem] = 0;
}

void sem_init() {
	for (int i = 0; i < _SEM_MAX_; i++) {
		_v_sem_[i] = 0;
	}
}
