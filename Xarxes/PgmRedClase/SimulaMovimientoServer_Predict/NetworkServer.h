#pragma once
#include <UDPSocket.h>
#include <vector>
#include "ClientProxy.h"
#include "GameServerConstants.h"

class NetworkServer
{
private:
	UDPSocket udpSocket;
	ClientProxy aPlayers[MAX_PLAYERS];
	bool aPlayersConnected[MAX_PLAYERS];
	bool Dispatch_Message(std::string _message, SocketAddress _saClient);
	int ExistClientProxy(ClientProxy _clientProxy);
	int GetNumPlayers();
	int GetPositionFreePlayer();
public:
	NetworkServer(std::string _strServerAddress);
	bool Receive();
	void SendToAll(std::string _message);
	~NetworkServer();
};