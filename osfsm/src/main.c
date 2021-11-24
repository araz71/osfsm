#include<stdio.h>
#include <time.h>
#include <stdint.h>
#include <delay.h>
#include <fsm.h>
#include <def.h>
#include <sem.h>

void fsm_test1(uint8_t _mid, uint8_t *_st) {
	uint8_t state = *_st;

	debug("TEST-1-STATE : %d\r", state);
	fflush(stdout);

	if (state == 0) {
		DELAY(1000);
		state = 1;
	} else if (state == 1) {
		DELAY(1000);
		state = 0;
	}

	*_st = state;
}

void fsm_test2(uint8_t _mid, uint8_t *_st) {
	uint8_t state = *_st;

	debug("TEST-2-STATE : %d\r", state);
	fflush(stdout);

	if (state == 0) {
		DELAY(500);
		state = 10;
	} else if (state == 10) {
		DELAY(5000);
		state = 0;
	}

	*_st = state;
}

void fsm_semTest1(uint8_t _mid, uint8_t *_st) {
	uint8_t state = *_st;

	if (state == 0) {
		SEM_WAIT(SEM_PRINT);
		state = 1;
	} else if (state == 1) {
		debug("AT %u : NOW SEM IS MINE!\r", (uint32_t)SysTickCntr);
		DELAY(1000);
		state = 2;
	} else if (state == 2) {
		sem_free(SEM_PRINT);
		state = 0;
	}

	*_st = state;
}

void fsm_semTest2(uint8_t _mid, uint8_t *_st) {
	uint8_t state = *_st;

	if (state == 0) {
		SEM_WAIT(SEM_PRINT);
		state = 1;
	} else if (state == 1) {
		debug("AT %u : NOW SEM IS MINE!\r", (uint32_t)SysTickCntr);
		DELAY(2000);
		state = 2;
	} else if (state == 2) {
		sem_free(SEM_PRINT);
		state = 0;
	}

	*_st = state;
}
int main(void) {
	clock_t tick = 0;

	fsm_init();

	fsm_add(fsm_test1);
	fsm_add(fsm_test2);

	fsm_add(fsm_semTest1);
	fsm_add(fsm_semTest2);
	while (1) {
		if (tick != clock()) {
			tick = clock();
			SysTickCntr++;
		}

		fsm_manager();
	}

	return 0;
}
