#include<stdio.h>
#include <time.h>
#include <stdint.h>
#include <fsm.h>
#include <delay.h>

void fsm1(struct fsm_st* fsm) {
	if (fsm->step == 0) {
		printf("this is my first step\r\n");
		fflush(stdout);
		fsm_delay(fsm, 1);
		fsm->step++;
	} else if (fsm->step == 1) {
		printf("this is my second step\r\n");
		fflush(stdout);
		fsm_delay(fsm, 1);
		fsm->step++;
	} else if (fsm->step == 2) {
		fsm->step = 0;
	}
}

uint8_t ready = 0;
uint64_t ready_wait_timestamp;

uint8_t wait_for_ready() {
	return ready;
}

void fsm2(struct fsm_st* fsm) {
	if (fsm->step == 0) {
		fsm_wait(fsm, &wait_for_ready, 0);
		fsm->step++;
	} else if (fsm->step == 1) {
		printf("chatdi\r\n");
		fflush(stdout);
		fsm->step = 2;
	}
}

int main(void) {

	make_fsm(&fsm1);
	make_fsm(&fsm2);

	tick_cntr = 0;

	time_t now = time(NULL);
	ready_wait_timestamp = now;
	while(1) {
		fsm_manager();

		if ((time(NULL) - now) > 0) {
			now = time(NULL);
			tick_count();
		}

		if ((now - ready_wait_timestamp) >= 5)
			ready = 1;
	}
	return 0;
}
