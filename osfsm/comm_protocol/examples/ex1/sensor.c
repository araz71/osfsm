#include <delay.h>
#include <danish_link.h>
#include <danish.h>

#include <sys/socket.h>

#include <netinet/in.h>
#include <netinet/ip.h>

#include <net/if.h>

#define MY_ADDRESS		10

int socket_descriptor;
struct sockaddr_in send_address;

void writer(uint8_t* buffer, uint16_t size) {
	sendto(socket_descriptor, buffer, size, 0, (struct sockaddr*)&send_address, sizeof(send_address));
}

int main()
{
	uint8_t receive_buffer[1024];

	struct sockaddr_in receive_address;
	struct ifreq interface;

	socket_descriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (socket_descriptor == -1) {
		mlog("Can not create socket!\r\n");
		exit(EXIT_FAILURE);
	}

	memset(&interface, 0, sizeof(interface));
	strcpy(interface.ifr_name, "lo");
	if (setsockopt(socket_descriptor, SOL_SOCKET, SO_BINDTODEVICE, &interface, sizeof(interface)) < 0) {
		mlog("Can not bind socket to lo\r\n");
		exit(EXIT_FAILURE);
	}

	receive_address.sin_family = AF_INET;
	receive_address.sin_port = htons(12345);
	receive_address.sin_addr.s_addr = htons(INADDR_ANY);

	memcpy(&send_address, &receive_address, sizeof(send_address));

	while(1) {
		writer("Salam", 5);
		
		uint16_t receive_size = recvfrom(socket_descriptor, receive_buffer, 1024, 0,
				(struct sockaddr*)&receive_address, sizeof(receive_address));

		if (receive_size) {
			for (uint16_t i = 0; i < receive_size; i++) {
				if ((i%16) == 0)
					printf("\r\n");
				
				printf("%02x ", receive_buffer[i]);
			}
		}
	
		sleep(1);		
	}

	return 1;
}
