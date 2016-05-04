#pragma once
#include "ClientProxy.h"
#include "ListWords.h"

class Server
{
private:
	std::vector<ClientProxy> aClients;
	TCPSocket dispatcher;
	ListWords aWords;
	std::string CreateMsgRanking();

public:
	Server(std::string _serverAddress, int _numPlayers);
	void LoadingPlayers(int _numPlayers);
	void SendMsgAll(std::string _message);
	void ReceiveAndProcessMsgClients();
	bool ProcessMessage(std::string _message, int _numClient);
	bool SendWord();
	~Server();
};

