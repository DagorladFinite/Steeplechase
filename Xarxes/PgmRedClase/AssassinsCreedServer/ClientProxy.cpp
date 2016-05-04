#pragma once
#include "ClientProxy.h"

ClientProxy::ClientProxy(): playerState(PLAYER_STATE_ALIVE)
{
}

void ClientProxy::SetSocket(std::shared_ptr<TCPSocket> _tcpSocket)
{
	this->tcpSocket = _tcpSocket;
}

std::string ClientProxy::GetNick()
{
	return nick;
}

void ClientProxy::SetNick(std::string _nick)
{
	nick = _nick;
}


int ClientProxy::GetPlayerState()
{
	return playerState;
}

void ClientProxy::SetPlayerState(int _playerState)
{
	playerState = _playerState;
}

int ClientProxy::GetPlayerRole()
{
	return playerRole;
}

void ClientProxy::SetPlayerRole(int _playerRole)
{
	playerRole = _playerRole;
}


int ClientProxy::Send(std::string _msg)
{
	int err = tcpSocket->Send(_msg.c_str());
	return err;
}

int ClientProxy::Receive(std::string & _msg)
{
	char buffer[1300];
	int err = tcpSocket->Receive(buffer, 1300);
	if (err > -1)
	{
		if (err < 1300)
		{
			buffer[err] = '\0';
		}
		_msg = buffer;
	}
	return err;
}

bool ClientProxy::operator==(ClientProxy & _clientProxy)
{
	bool equals = _clientProxy.nick == nick;
	return equals;
}

ClientProxy::~ClientProxy()
{

}