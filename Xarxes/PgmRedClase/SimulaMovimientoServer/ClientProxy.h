#pragma once
#include <string>
#include <time.h>
#include <SocketAddress.h>
#include <LittleSquare.h>

class ClientProxy
{
private:
	std::string nick;
	LittleSquare littleSquare;
	SocketAddress saClient;

public:
	ClientProxy();
	ClientProxy(SocketAddress _saClient);
	ClientProxy(std::string _nick, SocketAddress _saClient);
	ClientProxy(const ClientProxy& _clientProxy);
	bool operator==(ClientProxy& _clientProxy);
	int GetPositionSquare();
	int ChangeMove(int _move);
	void SetNick(std::string _nick);
	SocketAddress& GetSocketAddress();
	~ClientProxy();
};