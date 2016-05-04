#pragma once
#include <vector>

#include "ClientProxy.h"
#include <UDPSocket.h>
class Server
{
	std::vector<ClientProxy> aPlayers;
	
	UDPSocket udpSocket;
	
public:
	Server(std::string _serverAddress);
	void LoadingPlayers();
	void SendToAll(std::string _message);
	int Receive(std::string& _message);
	int Send(std::string _message, SocketAddress& _address);
	void NonBlocking(bool _ok);
	~Server();
};

