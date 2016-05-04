#pragma once
#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>
#include <memory>
#include <iostream>

class SocketAddress
{
	sockaddr_in sa_in;
public:
	SocketAddress();
	SocketAddress(uint8_t num1, uint8_t num2, uint8_t num3, uint8_t num4, uint16_t puerto);
	SocketAddress(SocketAddress& sa);
	friend std::ostream& operator<<(std::ostream& os, SocketAddress& sa);
	int SetAddress(const std::string & inString);
	~SocketAddress();
};

