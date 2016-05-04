#pragma once
#include <UDPSocket.h>
#include <GameConstants.h>
#include "GameConstantsClient.h"
#include "ListOfMonsters.h"
#include <time.h>

class Network
{
private:
	UDPSocket udpSocket;
	SocketAddress saServer;
	std::string nick;
	NetworkClientState networkState;
	clock_t mTimeOfLastHello;
	
public:
	Network(std::string _addressServer, std::string _addressClient, std::string _nick);
	void Send(std::string _message);
	int Receive(std::string& _message);
	void NonBlocking(bool _ok);
	NetworkClientState GetState();
	void SetState(NetworkClientState _state);
	
	void SayHello();
	void ProcessWelcome();
	void ProcessMonsters(ListOfMonsters& _listOfMonsters, std::string _strMonsters);
	
	~Network();
};

