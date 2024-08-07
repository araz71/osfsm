#ifndef SHM_H_
#define SHM_H_

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <log.h>

typedef uint8_t shm_id;

#define SHM_MAX		1

#pragma pack(push)
#pragma pack(1)
typedef struct {
	uint8_t *ptr;
	uint8_t lock;
	const char* pid;
} sshm;
#pragma pack(pop)

void shm_init();
uint8_t shm_lock(shm_id id, const char* pid);
uint8_t shm_unlock(shm_id id, const char* pid);
shm_id shm_add(void* pointer2buf);
uint8_t* shm_get(shm_id id);

#endif
