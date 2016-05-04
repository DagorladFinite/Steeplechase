#include "ClientProxy.h"



ClientProxy::ClientProxy()
{
}

ClientProxy::ClientProxy(const std::string _nick, const SocketAddress & _sa):nick(_nick)
{
	clientIPPort = _sa;
}

ClientProxy::ClientProxy(const ClientProxy & clientProxy):ClientProxy(clientProxy.nick, clientProxy.clientIPPort)
{
}

bool ClientProxy::operator==(ClientProxy & _clientProxy)
{
	if (_clientProxy.clientIPPort == clientIPPort && nick == _clientProxy.nick)
	{
		return true;
	}
	return false;
}

bool ClientProxy::Contains(std::vector<ClientProxy>& _aPlayers, ClientProxy & _clientProxy)
{
	for (size_t i = 0; i < _aPlayers.size(); i++)
	{
		if (_aPlayers[i] == _clientProxy)
		{
			return true;
		}
	}
	
	return false;
}


ClientProxy::~ClientProxy()
{
}
