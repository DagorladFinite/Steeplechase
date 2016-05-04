#pragma once
#include <TCPSocket.h>
#include "UserData.h"

class NetworkClient
{
private:
	TCPSocket tcpSocket;
	UserData* userData;
	int role;
	std::string nick;
public:
	NetworkClient(std::string _serverAddress, std::string _nick, UserData* _userData);
	int Receive(std::string& _message);
	int Send(std::string _message);
	void ProcessMessage(std::string _message);
	~NetworkClient();
};

