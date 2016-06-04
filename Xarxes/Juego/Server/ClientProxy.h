#pragma once
#include <string>
#include <time.h>
#include <SocketAddress.h>


class ClientProxy
{
private:
	std::string nick;
	SocketAddress saClient;
	
	

public:
	ClientProxy();
	ClientProxy(std::string _nick, SocketAddress _saClient);
	bool operator==(ClientProxy& _clientProxy);
	int GetPosition();
	void SetAddress(SocketAddress address);
	void SetNick(std::string _nick);
	SocketAddress& GetSocketAddress();
	~ClientProxy();

	bool connected = false;
	int position;
	int antiCheatCount;
};

