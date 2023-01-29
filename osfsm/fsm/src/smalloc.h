#ifndef SMALLOC_H
#define SMALLOC_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define SMALLOC_BUFFER_SIZE     2048
#define SMALLOC_PAGE_SIZE      	64
#define SMALLOC_PAGES_AVAL     	SMALLOC_BUFFER_SIZE / SMALLOC_PAGE_SIZE

uint8_t smalloc_buffer[SMALLOC_BUFFER_SIZE];

struct smalloc_buffer_pages_st{
    uint8_t allocated;
    uint16_t page_len;
} smalloc_pages[SMALLOC_PAGES_AVAL];

uint8_t *smem_alloc(uint32_t size);
void smem_free(uint8_t *mem_addr);
void smem_print();
#endif