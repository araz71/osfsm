#include "danish.h"


int main() {
	//create a packet
	uint8_t data[10];
	uint8_t result[20];

	//must make successfull and return size of packet
	uint8_t len = danish_make(10, FUNC_WRITE, 1203, 10, data, result);
	if (len == 0) printf("%d : packet must create successfull but failed\r\n", __LINE__);
	if (len < 17) printf("%d : packet size is wrong\r\n", __LINE__);

	//check for validity
	if (result[PACKET_ADDRESS] != 10) printf("%d : packet make failed\r\n", __LINE__);
	if (result[PACKET_FUNCTION] != FUNC_WRITE) printf("%d : packet make failed\r\n", __LINE__);
	if (result[PACKET_REG_ID_MSB] != (1203 >> 8)) printf("%d : packet make failed\r\n", __LINE__);
	if (result[PACKET_REG_ID_LSB] != (1203 & 0xFF)) printf("%d : packet make failed\r\n", __LINE__);
	if (result[PACKET_LEN] != 10) printf("%d : packet make failed\r\n", __LINE__);
	if (memcmp(&result[PACKET_DATA], data, 10) != 0) printf("packet make failed\r\n", __LINE__);

	//open packet with danish_ach
	danish_st my_packet;
	uint8_t my_data[20];
	mu_packet.data = my_data;
	int8_t ret = danish_ach(result, len, &my_packet);

	if (my_packet.function != FUNC_WRITE) printf("%d : packet ach failed", __LINE__);

	return 1;
}
