/*
 * fsm.h
 *
 *  Created on: Oct 20, 2021
 *      Author: Duman
 */

#ifndef FSM_H_
#define FSM_H_

#include <fsm/fsmdef.h>


typedef enum {
	FSM_FLAG_TIMEOUT		= 0x01,
	FSM_FLAG_DELAY			= 0x02,
	FSM_FLAG_CALLBACK		= 0x04,
} fsm_flags_enu;
typedef enum {
	FSM_ST_RUN,
	FSM_ST_DELAY,
	FSM_ST_CALLBACK,
	FSM_ST_SUSPEND,
} fsm_st_enu;
typedef struct {
	void (*fsm_cb)(fsm_flags_enu _flags);
	uint64_t ts;
	uint32_t delay;
	uint8_t (*callback)(void);
	fsm_st_enu state;
} fsm_st;

fsmID fsm_req(void (*_fsm)(fsm_flags_enu _flags));
void fsm_delay_ms(fsmID _fid, uint32_t _delay);
void fsm_delay_s(fsmID _fid, uint32_t _delay);
void fsm_delay_m(fsmID _fid, uint32_t _delay);
void fsm_wait4callback(fsmID _fid, uint8_t (*_callback)(void), uint32_t _timeout_ms);
void fsm_manager();


#define FSM_MAKE(ME)	static fsmID mID = FSM_UNDEF;	\
						if (mID == FSM_UNDEF) { \
							mID = fsm_req(ME);	\
							return;\
						}
#define FSM_DELAY_MS(MS)		fsm_delay_ms(mID, MS)
#define FSM_DELAY_S(S)			fsm_delay_s(mID, S)
#endif /* FSM_H_ */
