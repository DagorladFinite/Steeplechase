#pragma once
#include <SocketAddress.h>
#include <vector>
class ClientProxy
{
private:
	SocketAddress clientIPPort;
	std::string nick;
	friend class Server;
public:
	ClientProxy();
	ClientProxy(const std::string _nick, const SocketAddress& _sa);
	ClientProxy(const ClientProxy& _clientProxy);
	bool operator==(ClientProxy& _clientProxy);
	static bool Contains(std::vector<ClientProxy>& _aPlayers, ClientProxy& _clientProxy);
	~ClientProxy();
};

