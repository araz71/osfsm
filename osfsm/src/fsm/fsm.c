/*
 * fsm.c
 *
 *  Created on: Oct 20, 2021
 *      Author: Duman
 */


#include <fsm/fsm.h>
#include <stdlib.h>
#include <stdint.h>

static uint8_t _v_fsm_cntr_ = 0;
static fsm_st _v_fsms_[FSM_MAX_AVAL];

fsmID fsm_req(void (*_fsm)(fsm_flags_enu _flags)) {
	if (_v_fsm_cntr_ >= FSM_MAX_AVAL) return FSM_UNDEF;

	_v_fsms_[_v_fsm_cntr_].callback = NULL;
	_v_fsms_[_v_fsm_cntr_].delay = 0;
	_v_fsms_[_v_fsm_cntr_].fsm_cb = _fsm;
	_v_fsms_[_v_fsm_cntr_].ts = 0;
	_v_fsms_[_v_fsm_cntr_].state = FSM_ST_RUN;
	_v_fsm_cntr_++;
	return _v_fsm_cntr_ - 1;
}

void fsm_delay_ms(fsmID _fid, uint32_t _delay) {
	_v_fsms_[_fid].ts = get_timestamp();
	_v_fsms_[_fid].delay = _delay;
	_v_fsms_[_fid].state = FSM_ST_DELAY;
}
void fsm_delay_s(fsmID _fid, uint32_t _delay) {
	_v_fsms_[_fid].ts = get_timestamp();
	_v_fsms_[_fid].delay = _delay * 1000;
	_v_fsms_[_fid].state = FSM_ST_DELAY;
}
void fsm_delay_m(fsmID _fid, uint32_t _delay) {
	_v_fsms_[_fid].delay = _delay;
	_v_fsms_[_fid].ts = get_timestamp();
	_v_fsms_[_fid].state = FSM_ST_DELAY;
}
void fsm_wait4callback(fsmID _fid, uint8_t (*_callback)(void), uint32_t _timeout_ms) {
	_v_fsms_[_fid].callback = _callback;
	_v_fsms_[_fid].state = FSM_ST_DELAY;
	_v_fsms_[_fid].ts = get_timestamp();
	_v_fsms_[_fid].delay = _timeout_ms;
}

uint8_t delay_ms(uint64_t _ts, uint32_t _delay) {
	if ((get_timestamp() - _ts) >= _delay) return 1;
	return 0;
}

void fsm_manager() {
	fsm_st_enu state;
	fsm_flags_enu flags;
	fsm_st *fsmInf;

	for (uint8_t fsmCntr = 0; fsmCntr < _v_fsm_cntr_; fsmCntr++) {
		fsmInf = &_v_fsms_[fsmCntr];
		state = fsmInf->state;
		if (state == FSM_ST_RUN) {
			fsmInf->fsm_cb(0);
		} else if (state == FSM_ST_DELAY) {
			if (delay_ms(fsmInf->ts, fsmInf->delay)) {
				fsmInf->state = FSM_ST_RUN;
				fsmInf->fsm_cb(FSM_FLAG_DELAY);
			}
		} else if (state == FSM_ST_CALLBACK) {
			flags = 0;
			if (fsmInf->callback()) flags = FSM_FLAG_CALLBACK;
			if (fsmInf->delay > 0 && delay_ms(fsmInf->ts, fsmInf->delay)) flags = FSM_FLAG_TIMEOUT;
			if (flags) {
				fsmInf->state = FSM_ST_RUN;
				fsmInf->fsm_cb(flags);
			}
		}
	}
}
