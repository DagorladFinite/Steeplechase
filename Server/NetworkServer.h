#pragma once
#include "ClientProxy.h"
#include <UDPSocket.h>
class NetworkServer
{
private:

	
	UDPSocket udpSocket;
	ClientProxy playerList[4];
	bool processMessage(std::string _message, SocketAddress _saClient);


public:
	NetworkServer(std::string _strServerAddress);
	~NetworkServer();
	bool Receive();
	void SendToAll(std::string _message);
	int playerlibre = 0;
	
};

