#pragma once
#include <TCPSocket.h>
#include "UserData.h"

class NetworkManager
{
private:
	TCPSocket tcpSocket;
	UserData* userData;
	std::string wordToCopy;
	std::string nick;

public:
	NetworkManager(std::string _serverAddress, std::string _nick, UserData* _userData);
	int Receive(std::string& _message);
	int Send(std::string _message);
	void ProcessMessage(std::string _message);
	~NetworkManager();
};

