#include "ClientProxy.h"

ClientProxy::ClientProxy()
{

}


ClientProxy::ClientProxy(std::string _nick, SocketAddress _saClient) : nick(_nick), saClient(_saClient)
{

}

bool ClientProxy::operator==(ClientProxy & _clientProxy)
{
	return saClient == _clientProxy.saClient;
}

int ClientProxy::GetPosition()
{
	return position;
}

void ClientProxy::SetAddress(SocketAddress address)
{

	saClient = address;
}

void ClientProxy::SetNick(std::string _nick)
{
	nick = _nick;
}

SocketAddress & ClientProxy::GetSocketAddress()
{
	return saClient;
}

ClientProxy::~ClientProxy()
{

}
