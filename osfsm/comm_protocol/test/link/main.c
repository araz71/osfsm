#include <stdio.h>
#include <danish_link.h>

uint8_t reg120_buffer[10];

void reg120_filled(uint8_t addr) {
	printf("reg120 filled by %d\r\n", addr);
	for (int i = 0; i < 10; i++) {
		printf("%02x ", reg120_buffer[i]);
	}
	printf("\r\n");
}

void reg120_readed(uint8_t addr) {
	printf("reg120 readed by %d\r\n", addr);
}

void danish_write_interface(uint8_t* data, uint16_t size) {
	printf("\r\n**************Request to transmit**************");
	for (int i = 0; i < size; i++) {
		danish_yiq(data[i]);
		if ((i%8) == 0) printf("\r\n");
		printf("%02x ", data[i]);
	}
	printf("\r\n***********************************************\r\n");
}

int main() {
	danish_link_init(&danish_write_interface);
	danish_add_register(120, reg120_buffer, sizeof(reg120_buffer), &reg120_filled, &reg120_readed);

	uint8_t *buffer = malloc(sizeof(reg120_buffer));
	memset(buffer, 0xA5, sizeof(reg120_buffer));
//	danish_req_reg_write(1, 120, buffer);
	danish_req_reg_read(1, 120);
	while (1) {
		danish_machine();
	}
	return 1;
}
