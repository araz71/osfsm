#include "osfsm_model.h"

static pthread_t osfsm_thread;
static pthread_mutex_t osfsm_put_mutex = PTHREAD_MUTEX_INITIALIZER;

static void *osfsm_handler(void* args) {
	while (1) {
		pthread_mutex_lock(&osfsm_put_mutex);
        fsm_manager();
		pthread_mutex_unlock(&osfsm_put_mutex);
	}
}

void osfsm_model_reinit() {
	pthread_mutex_lock(&osfsm_put_mutex);
	fsm_init();
	pthread_mutex_unlock(&osfsm_put_mutex);
}

void osfsm_model_put(void (*machine)(struct fsm_st* fsm)) {
	pthread_mutex_lock(&osfsm_put_mutex);
	make_fsm(machine);
	pthread_mutex_unlock(&osfsm_put_mutex);
}

void osfsm_model_init() {
#ifdef DEBUG
	printf("Model: Osfsm started...\r\n");
#endif
	pthread_create(&osfsm_thread, NULL, osfsm_handler, NULL);
}
