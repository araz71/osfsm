#include <shm.h>

static sshm shms[SHM_MAX];
static uint8_t shm_counter = 0;

void shm_init() {
	memset((uint8_t*)shms, 0, sizeof(sshm) * SHM_MAX);
	shm_counter = 0;
}

uint8_t shm_lock(shm_id id, char* pid) {
	if (shms[id].lock == 0 || (uint32_t)shms[id].pid == (uint32_t)pid) {
		shms[id].lock = 1;
		shms[id].pid = pid;
		mlog("Shared memory[%d] allocated by %s", id, pid);
		return 1;
	}
	return 0;
}

uint8_t shm_unlock(shm_id id, char* pid) {
	if (shms[id].lock == 1 && (uint32_t)shms[id].pid == (uint32_t)pid) {
		shms[id].lock = 0;
		mlog("Shared memory[%d] freed by %s\r\n", id, pid);
		shms[id].pid = NULL;
		return 1;
	}
	return 0;
}

shm_id shm_add(void* pointer2buf) {
	if (shm_counter >= SHM_MAX) return 0xFF;
	shms[shm_counter].ptr = pointer2buf;
	shm_counter++;
	return shm_counter - 1;
}

uint8_t* shm_get(shm_id id) {
	return shms[id].ptr;
}
