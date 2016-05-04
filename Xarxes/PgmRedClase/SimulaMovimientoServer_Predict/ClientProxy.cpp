#include "ClientProxy.h"
#include "GameServerConstants.h"

ClientProxy::ClientProxy(): nick(""), littleSquare(MIN_SQUARE)
{
	
}

ClientProxy::ClientProxy(SocketAddress _saClient): littleSquare(MIN_SQUARE), saClient(_saClient)
{
}

ClientProxy::ClientProxy(std::string _nick, SocketAddress _saClient) : nick(_nick), littleSquare(MIN_SQUARE), saClient(_saClient)
{

}

ClientProxy::ClientProxy(const ClientProxy & _clientProxy):nick(_clientProxy.nick), littleSquare(_clientProxy.littleSquare)
{
	
	saClient = _clientProxy.saClient;
}

bool ClientProxy::operator==(const ClientProxy & _clientProxy)
{
	return saClient == _clientProxy.saClient;
}

int ClientProxy::GetPositionSquare()
{
	return littleSquare.GetPosition();
}

int ClientProxy::ChangeMove(int _move)
{
	int position = littleSquare.GetPosition();
	int positionAux = position + _move;
	if (positionAux < MIN_SQUARE)
	{
		positionAux = MIN_SQUARE;
	}
	else if (positionAux > MAX_SQUARE)
	{
		positionAux = MAX_SQUARE;
	}
	littleSquare.SetPosition(positionAux);
	return positionAux;
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