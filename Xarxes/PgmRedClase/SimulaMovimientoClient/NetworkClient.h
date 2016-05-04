#pragma once
#include <UDPSocket.h>
#include "GameClientConstants.h"
#include "InputState.h"
#include <time.h>

class NetworkClient
{
private:
	UDPSocket udpSocket;
	SocketAddress saServer;
	std::string nick;
	int idSquare;
	NetworkState networkState;
	clock_t timeOfLastHello;
	clock_t timeOfLastMove;

public:
	NetworkClient(std::string _addressServer, std::string _addressClient, std::string _nick);
	
	NetworkState GetNetworkState();
	void SetNetworkState(NetworkState _networkState);
	int GetIdSquare();
	void SetIdSquare(int _idSquare);

	void SayHello();
	void SendCommand(InputState& _inputState);
	
	void Send(std::string _message);
	int Receive(std::string& _message);
	
	~NetworkClient();
};

