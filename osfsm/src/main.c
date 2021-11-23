#include<stdio.h>
#include <time.h>
#include <stdint.h>
#include <delay.h>
#include <fsm.h>

void fsm_test1(uint8_t _mid, uint8_t *_st) {
	uint8_t state = *_st;

	printf("TEST-1-STATE : %d\r", state);
	fflush(stdout);

	if (state == 0) {
		DELAY(1000);
		state = 1;
	} else if (state == 1) {
		DELAY(3000);
		state = 0;
	}

	*_st = state;
}

void fsm_test2(uint8_t _mid, uint8_t *_st) {
	uint8_t state = *_st;

	printf("TEST-2-STATE : %d\r", state);
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
int main(void) {
	clock_t tick = 0;

	printf("START\r\n");
	fflush(stdout);

	fsm_add(fsm_test1);
	fsm_add(fsm_test2);

	while (1) {
		if (tick != clock()) {
			tick = clock();
			SysTickCntr++;
		}

		fsm_manager();
	}

	return 0;
}
