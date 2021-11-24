/*
 * def.h
 *
 *  Created on: Nov 23, 2021
 *      Author: Amin Aghakhani
 */

#ifndef DEF_H_
#define DEF_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <delay.h>

#define FSM_MAX_AVAL		10

typedef enum {
	SEM_PRINT,
	_SEM_MAX_,
} sem_enu;

typedef enum {
	RET_FALSE,
	RET_TRUE,

	RET_BUSY = 255,
} ret_enu;

#define debug(...)		\
	printf("%-20s - %03d : ", __FILE__, __LINE__);	\
	printf(__VA_ARGS__);	\
	fflush(stdout);

#endif /* DEF_H_ */
