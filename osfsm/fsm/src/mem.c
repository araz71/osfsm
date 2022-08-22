#include <mem.h>

static uint8_t buffer[BUFFER_SIZE];

struct buffer_pages_st{
    uint8_t allocated;
    uint16_t page_len;
} pages[BUFFER_SIZE / PAGE_SIZE];

uint8_t *mem_alloc(uint32_t size) {
    uint8_t page_needed = size / PAGE_SIZE;
    if ((size%PAGE_SIZE) != 0) page_needed++;
    uint8_t bir_sira_page_sayan = 0;

    for (int i = 0; i < PAGES_AVAL; i++) {
        if (pages[i].allocated == 0) {
            for (int j = i; j < PAGES_AVAL; j++) {
                if (pages[j].allocated == 0) bir_sira_page_sayan++;
                if (bir_sira_page_sayan >= page_needed) {
                    pages[i].page_len = page_needed;
                    for (int l = i; l <= j; l++) {
                        pages[l].allocated = 1;
                    }
                    return &buffer[i * PAGE_SIZE];
                }
            }
            bir_sira_page_sayan = 0;
        }
    }
    return NULL;
}

void mem_free(uint8_t *mem) {
    if (mem != NULL) {
        uint32_t offset = ((uint32_t)mem) - ((uint32_t)buffer);
        offset /= PAGE_SIZE;
        pages[offset].allocated = 0;
        for (int i = 0; i < pages[offset].page_len; i++) {
            printf("free %d\r\n", offset + i);
            pages[offset + i].allocated = 0;
        }
    }
}

void mem_print() {
    for (int i = 0; i < PAGES_AVAL; i++) {
        if (pages[i].allocated) {
            if (pages[i].page_len == 1) {
                printf("page %d is allocated\r\n", i);
            } else if (pages[i].page_len > 1) {
                printf("page %d to %d are allocated\r\n", i, i + pages[i].page_len - 1);
                i += pages[i].page_len;
                i--;
            } else {
                printf("error on page %d\r\n", i);
            }
        }
    }
}