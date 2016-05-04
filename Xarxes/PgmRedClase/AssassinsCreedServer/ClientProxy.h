#pragma once
#include <TCPSocket.h>
#include "GameConstants.h"

class ClientProxy
{
private:
	std::string nick;
	int playerState;
	int playerRole;
	std::shared_ptr<TCPSocket> tcpSocket;

public:
	ClientProxy();
	bool operator==(ClientProxy& _clientProxy);
	
	void SetSocket(std::shared_ptr<TCPSocket> _tcpSocket);
	std::string GetNick();
	void SetNick(std::string _nick);
	int GetPlayerState();
	void SetPlayerState(int _playerState);
	int GetPlayerRole();
	void SetPlayerRole(int _playerRole);

	int Send(std::string _msg);
	int Receive(std::string& _msg);
	~ClientProxy();
};