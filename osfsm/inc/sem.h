/*
 * sem.h
 *
 *  Created on: Nov 23, 2021
 *      Author: Zeinab
 */

#ifndef SEM_H_
#define SEM_H_

#include <def.h>

ret_enu sem(sem_enu _sem);
ret_enu sem_busy(sem_enu _sem);
void sem_free(sem_enu _sem);
void sem_init();

#endif /* SEM_H_ */
