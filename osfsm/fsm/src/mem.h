#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define BUFFER_SIZE     2048
#define PAGE_SIZE       64
#define PAGES_AVAL      BUFFER_SIZE / PAGE_SIZE

uint8_t *mem_alloc(uint32_t size);
void mem_free(uint8_t *mem);
void mem_print();