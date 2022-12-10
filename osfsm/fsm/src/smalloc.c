#include <smalloc.h>

uint8_t *smalloc(uint32_t size) {
    uint8_t page_needed = size / SMALLOC_PAGE_SIZE;
    if ((size%SMALLOC_PAGE_SIZE) != 0) page_needed++;
    uint8_t bir_sira_page_sayan = 0;

    for (int i = 0; i < SMALLOC_PAGES_AVAL; i++) {
        if (smalloc_pages[i].allocated == 0) {
            for (int j = i; j < SMALLOC_PAGES_AVAL; j++) {
                if (smalloc_pages[j].allocated == 0) bir_sira_page_sayan++;
                if (bir_sira_page_sayan >= page_needed) {
                	smalloc_pages[i].page_len = page_needed;
                    for (int l = i; l <= j; l++) {
                    	smalloc_pages[l].allocated = 1;
                    }
                    return &smalloc_buffer[i * SMALLOC_PAGE_SIZE];
                }
            }
            bir_sira_page_sayan = 0;
        }
    }
    return NULL;
}

void smem_free(uint8_t *mem_addr) {
    if (mem_addr != NULL) {
        uint32_t offset = ((uint32_t)mem_addr) - ((uint32_t)smalloc_buffer);
        offset /= SMALLOC_PAGE_SIZE;
        smalloc_pages[offset].allocated = 0;
        for (int i = 0; i < smalloc_pages[offset].page_len; i++) {
            printf("free %d\r\n", offset + i);
            smalloc_pages[offset + i].allocated = 0;
        }
    }
}

void smem_print() {
    for (int i = 0; i < SMALLOC_PAGES_AVAL; i++) {
        if (smalloc_pages[i].allocated) {
            if (smalloc_pages[i].page_len == 1) {
                printf("page %d allocated\r\n", i);
            } else if (smalloc_pages[i].page_len > 1) {
                printf("page %d to %d are allocated\r\n", i, i + smalloc_pages[i].page_len - 1);
                i += smalloc_pages[i].page_len;
                i--;
            } else {
                printf("error on %d\r\n", i);
            }
        }
    }
}
