#include "danish.h"

int main() {
	//create a packet
	uint8_t data[10];
	uint8_t result[20];

	//must make successfull and return size of packet
	uint8_t len = danish_make(10, FUNC_WRITE, 1203, 10, data, result);
	if (len == 0) printf("%d : packet must create successfull but failed\r\n", __LINE__);
	if (len < 16) printf("%d : packet size is wrong\r\n", __LINE__);

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
	my_packet.data = my_data;
	int8_t ret = danish_ach(result, len, &my_packet);
	if (ret != 1) printf("%d : packet ach failed\r\n");

	if (my_packet.function != FUNC_WRITE) printf("%d : packet ach failed", __LINE__);
	if (my_packet.len != 10) printf("%d : packet ach failed in data len(%d)\r\n", __LINE__, my_packet.len);
	if (my_packet.address != 10) printf("%d : packet ach failed in address(%d)\r\n", __LINE__, my_packet.address);
	if (my_packet.regID != 1203) printf("%d : packet ach failed in register id(%d)\r\n", __LINE__, my_packet.regID);
	if (memcmp(my_packet.data, my_data, 10) != 0) printf("%d : packet ach failed in data\r\n", __LINE__);

	printf("Packet created and openned successfully :");
	printf("\tpacket size : %d\r\n", len);
	printf("\tpacket : ");
	for (int i = 0; i < len; i++) {
		printf("%02x ", result[i]);
	}
	printf("\r\n");

	return 1;
}
