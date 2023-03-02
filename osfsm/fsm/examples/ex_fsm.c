#include "fsm.h"

#include <stdio.h>

static uint64_t system_tick_cntr = 0;

uint64_t get_timestamp() {
	return system_tick_cntr;
}
void blinker(sfsm* fsm) {
	if (fsm->step == 0) {
		printf("ON\r\n");
		fsm_delay_jump(fsm, 1000, 1);
	} else if (fsm->step == 1) {
		printf("OFF\r\n");
		fsm_delay_jump(fsm, 1000, 0);
	}
}

int main() {
	clock_t timestamp = 0;
	make_fsm(&blinker);

	while (1) {
		fsm_manager();

		clock_t current_timestamp = clock();
		if ((current_timestamp - timestamp) >= 1000) {
			timestamp = current_timestamp;
			system_tick_cntr++;
		}
	}

	return 1;
}
