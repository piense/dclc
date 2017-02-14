#include "stdafx.h"
#include <winsock2.h>
#include <stdio.h>
#include "udp.h"
#include <Ws2tcpip.h>

void sendUDP(uint8_t* packetBytes, uint16_t packetLength, bool broadcast, uint16_t port) {

	SOCKET socketC;

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	struct sockaddr_in serverInfo;
	int len = sizeof(serverInfo);
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_port = htons(port);
	inet_pton(AF_INET, "192.168.0.255", &serverInfo.sin_addr);
	

	socketC = socket(AF_INET, SOCK_DGRAM, 0);

	if (sendto(socketC, (const char *)&packetBytes[0], packetLength, 0, (sockaddr*)&serverInfo, len) != SOCKET_ERROR)
	{
			//woohoo sent a packet
	}
	
	closesocket(socketC);


}

