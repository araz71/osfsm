#include<stdio.h>
#include <fsm/fsmdef.h>
#include <fsm/fsm.h>
#include <time.h>

void print1(fsm_flags_enu _flags) {
	static uint8_t st = 0;
	FSM_MAKE(&print1);

	if (st == 0) {
		printf("STATE 0\r\n");
		fflush(stdout);
		FSM_DELAY_MS(1000);
		st = 1;
	} else if (st == 1) {
		printf("STATE 1\r\n");
		fflush(stdout);

		FSM_DELAY_MS(100);
		st = 0;
	}
}

int main(void) {
	clock_t tick = 0;
	SysTickCntr = 0;

	printf("START\r\n");
	fflush(stdout);

	print1(0);

	while (1) {
		if (tick != clock()) {
			tick = clock();
			SysTickCntr++;
		}

		fsm_manager();
	}

	return 0;
}
