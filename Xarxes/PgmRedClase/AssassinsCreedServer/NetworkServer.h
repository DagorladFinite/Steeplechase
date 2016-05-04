#pragma once
#include <TCPSocket.h>
#include "ClientProxy.h"
#include <vector>

class NetworkServer
{
private:
	std::vector<ClientProxy> aClients;
	TCPSocket dispatcher;
	int numPlayers;
	int numNickArrived;
	std::string CreatePlayersGameState();
	int SearchByNick(std::string _nick);
	int GetNumDeads();
public:
	NetworkServer(std::string _serverAddress, int _numPlayers);
	void LoadingPlayers();
	void SendMsgAll(std::string _message);
	bool ReceiveAndProcessMsgClients();
	bool ProcessMessage(std::string _message, int _numClient);
	~NetworkServer();
};