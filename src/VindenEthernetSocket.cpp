#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <string.h>


int requestSocketFd;

struct sockaddr_in requestServerAddr;

#define CAMERA_PORT 14001
#define CAMERA_IP "192.168.111.109"

int main() {

	requestSocketFd = 0;

	memset(&requestServerAddr, 0, sizeof(requestServerAddr));

	requestServerAddr.sin_family = AF_INET;
	requestServerAddr.sin_port = htons(CAMERA_PORT);
	requestServerAddr.sin_addr.s_addr = inet_addr(CAMERA_IP);

	// Creaciòn de file descriptor para request (cliente)
	requestSocketFd = socket(AF_INET, SOCK_DGRAM, 0);
	if (requestSocketFd < 0)
	{
		return 1;
	}

	unsigned char data[] = { 0x51, 0xAC, 0x0C, 0x70, 0x00, 0x01, 0xBB, 0x6F, 0x03, 0x43, 0x00, 0x00, 0xFF, 0xFF, 0x59 };

	sendto(requestSocketFd, data, sizeof(data), MSG_CONFIRM, (const struct sockaddr *)&requestServerAddr, sizeof(requestServerAddr));

	return 0;
}
