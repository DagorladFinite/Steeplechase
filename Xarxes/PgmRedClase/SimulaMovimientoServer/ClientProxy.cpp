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

bool ClientProxy::operator==(ClientProxy & _clientProxy)
{
	return saClient == _clientProxy.saClient;
}

int ClientProxy::GetPositionSquare()
{
	return littleSquare.GetPosition();
}

/**
 * Comprobamos que esta posición no sobrepase el mínimo y el máximo
 * Si lo sobrepasa retornamos MIN_SQUARE o MAX_SQUARE, según el caso.
 */
int ClientProxy::ChangeMove(int _move)
{
	
	int posAct = littleSquare.GetPosition();
	int posTry = posAct + _move;
	if (posTry >= MIN_SQUARE && posTry <= MAX_SQUARE)
	{
		posAct = posTry;
	}
	littleSquare.SetPosition(posAct);
	return posAct;
	/*if (_move < MIN_SQUARE)
	{
		_move = MIN_SQUARE;
	}
	else if (_move > MAX_SQUARE)
	{
		_move = MAX_SQUARE;
	}
	littleSquare.SetPosition(_move);
	return _move;*/
	
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