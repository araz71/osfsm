#ifndef OSFSM_MODEL_H_
#define OSFSM_MODEL_H_

#include "fsm.h"
#include <pthread.h>

void osfsm_model_put(void (*machine)(struct fsm_st* fsm));
void osfsm_model_reinit();
void osfsm_model_init();

#endif