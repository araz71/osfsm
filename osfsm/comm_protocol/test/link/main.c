#include <stdio.h>
#include <danish_link.h>
#include <log.h>

uint8_t reg120_buffer[10];

uint8_t reg120_filled_flag = 0;
uint8_t reg120_readed_flag = 0;

void reg120_filled(uint8_t addr) {
	reg120_filled_flag = 1;
	printf("-> reg120 filled by %d\r\n", addr);
	printf("Data: ");
	for (int i = 0; i < 10; i++) {
		printf("%02x ", reg120_buffer[i]);
	}
	printf("\r\n\r\n");
}

void reg120_readed(uint8_t addr) {
	reg120_readed_flag = 1;
	printf("-> reg120 readed by %d\r\n", addr);
}

void reg120_write_ack() {
	printf("-> Write ack called\r\n");
}

void danish_write_interface(uint8_t* data, uint16_t size) {
	printf("\r\n**************Request to transmit**************");
	for (int i = 0; i < size; i++) {
		danish_yiq(data[i]);
		if ((i%16) == 0) printf("\r\n");
		printf("%02x ", data[i]);
	}
	printf("\r\n***********************************************\r\n\r\n");
}

int main() {
	uint8_t tester_st = 0;

	link_reg_st reg;

	danish_link_init(10, &danish_write_interface);

	reg.regID = 120;
	reg.ptr = reg120_buffer;
	reg.size = sizeof(reg120_buffer);
	reg.filled_callback = &reg120_filled;
	reg.read_callback = &reg120_readed;
	reg.write_ack_callback = &reg120_write_ack;	

	danish_add_register(&reg);

	uint8_t *buffer = malloc(sizeof(reg120_buffer));
	memset(buffer, 0xA5, sizeof(reg120_buffer));

	while (1) {
		if (tester_st == 0) {
			mlog("Writing on 120th register on device(10)");
			danish_write(10, 120, buffer);
			tester_st = 1;
		} else if (tester_st == 1) {
			if (reg120_filled_flag == 1) {
				mlog("Read for 120th register on device(10)");
				danish_read(10, 120);
				tester_st = 2;
			}
		} else if (tester_st == 2) {
			if (reg120_readed_flag == 1) {
				mlog("Well done");
				break;
			}
		}

		danish_machine();
	}
	return 1;
}
