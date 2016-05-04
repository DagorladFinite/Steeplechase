#pragma once
#include "NetworkServer.h"
#include "GameConstants.h"
#include <string>



NetworkServer::NetworkServer(std::string _serverAddress, int _numPlayers):numPlayers(_numPlayers), numNickArrived(0)
{
	SocketAddress sa;
	sa.SetAddress(_serverAddress);
	int err = dispatcher.Bind(sa);
	if (err == -1)
	{
		throw std::exception("Error en NetworkServer::Bind");
	}
	err = dispatcher.Listen(_numPlayers);
	if (err == -1)
	{
		throw std::exception("Error en NetworkServer::Listen");
	}
}

void NetworkServer::LoadingPlayers()
{
	int err;
	int idAssassin = rand() % numPlayers;
	int idPolice = rand() % numPlayers;
	while (idPolice == idAssassin)
	{
		idPolice = rand() % numPlayers;
	}

	for (int i = 0; i < numPlayers; i++)
	{
		SocketAddress from;
		std::shared_ptr<TCPSocket> tcpSocket = dispatcher.Accept(from);
		tcpSocket->NonBlocking(true);
		ClientProxy newClient;
		newClient.SetSocket(tcpSocket);
		
		int idRole = PLAYER_ROLE_VICTIM;
		if (i == idAssassin)
		{
			idRole = PLAYER_ROLE_ASSASSIN;
		}
		else if (i == idPolice)
		{
			idRole = PLAYER_ROLE_POLICE;
		}
		
		err = newClient.Send("ROLE_" + std::to_string(idRole));
		if (err == -1)
		{
			std::cout << "Error al enviar al cliente el rol " << i << " en NetworServer::LoadingPlayers" << std::endl;
		}
		newClient.SetPlayerRole(idRole);
		aClients.push_back(newClient);
	}

	SendMsgAll("BEGIN");
	
}

void NetworkServer::SendMsgAll(std::string _message)
{
	for (int i = 0; i < numPlayers; i++)
	{
		int err = aClients[i].Send(_message);
		if (err == -1)
		{
			std::cout << "Error al enviar al cliente " << i << std::endl;
		}
	}
}

/*
 *	Si retorna true es porque uno de los clientes se ha desconectado. En ese caso tenemos que acabar la partida.
 */
bool NetworkServer::ReceiveAndProcessMsgClients()
{
	for (int i = 0; i < numPlayers; i++)
	{
		std::string message;
		int err = aClients[i].Receive(message);
		if (err == 0)
		{
			return true;
		}
		
		bool exit = ProcessMessage(message, i);
		if (exit)
			return true;
	}
	return false;
}

bool NetworkServer::ProcessMessage(std::string _message, int _numClient)
{
	int index_ = _message.find_first_of('_');
	std::string cabecera = _message.substr(0, index_);
	std::string contenido = _message.substr(index_ + 1, _message.size() - index_);
	
	if (cabecera == HEADER_NICK)
	{
		aClients[_numClient].SetNick(contenido);
		numNickArrived++;
		if (numNickArrived == numPlayers)
		{
			std::string msg = CreatePlayersGameState();
			SendMsgAll(msg);
		}
	}
	else if (cabecera == HEADER_CHAT)
	{
		std::string nick = aClients[_numClient].GetNick();
		SendMsgAll("CHATNICK_" + nick + ":" + contenido);
	}
	else if (cabecera == HEADER_KILL)
	{
		int idRole = aClients[_numClient].GetPlayerRole();
		if (idRole != PLAYER_ROLE_ASSASSIN)
		{
			std::string msg = "MSGSERVER_";
			msg += "No eres el asesino, no puedes matar.";
			aClients[_numClient].Send(msg);
		}
		else
		{
			int index = SearchByNick(contenido);
			if (index == -1)
			{
				std::cout << "Intentan matar a un nick que no existe" << std::endl;
			}
			else if (index == _numClient)
			{
				std::string msg = "MSGSERVER_";
				msg += "No te puedes matar a ti mismo, tonto!";
				aClients[_numClient].Send(msg);
			}
			else
			{
				std::string msg = "MSGSERVER_";
				msg += "Te han matado";
				aClients[index].Send(msg);
				aClients[index].SetPlayerState(PLAYER_STATE_DEAD);
			}

			std::string msg = CreatePlayersGameState();
			SendMsgAll(msg);
			if (aClients[index].GetPlayerRole() == PLAYER_ROLE_POLICE)
			{
				msg = "MSGSERVER_";
				msg += "Han matado al policia. Acaba la partida.";
				SendMsgAll(msg);
				return true;
			}

			int numDeads = GetNumDeads();
			if (numDeads >= numPlayers - 2)
			{
				std::string msg = "MSGSERVER_";
				msg += "Todos muertos. Acaba la partida.";
				SendMsgAll(msg);
				return true;
			}
		}
	}
	else if (cabecera == HEADER_CATCHYOU)
	{
		int idRole = aClients[_numClient].GetPlayerRole();
		if (idRole != PLAYER_ROLE_POLICE)
		{
			std::string msg = "MSGSERVER_";
			msg += "No eres el policia, no puedes detener a nadie.";
			aClients[_numClient].Send(msg);
		}
		else
		{
			int index = SearchByNick(contenido);
			if (index == -1)
			{
				std::cout << "Intentan detener a un nick que no existe" << std::endl;
			}
			else if (index == _numClient)
			{
				std::string msg = "MSGSERVER_";
				msg += "No te puedes detener a ti mismo, tonto!";
				aClients[_numClient].Send(msg);
			}
			else if (aClients[index].GetPlayerRole() == PLAYER_ROLE_ASSASSIN)
			{
				std::string msg = "MSGSERVER_";
				msg += "Han pillado al asesino. Acaba la partida.";
				SendMsgAll(msg);
				return true;
			}
			else
			{
				std::string msg = "MSGSERVER_Has fallado. Este no es el asesino.";
				aClients[_numClient].Send(msg);
			}
		}
	}
	else if (cabecera == HEADER_RESEND)
	{
		std::string msg = CreatePlayersGameState();
		aClients[_numClient].Send(msg);
	}
	return false;
}

std::string NetworkServer::CreatePlayersGameState()
{
	std::string ret = "PLAYERGAMESTATE_";

	for (int i = 0; i < numPlayers; i++)
	{
		ret += std::to_string(i) + ". " + aClients[i].GetNick() + " - " + aStrStates[aClients[i].GetPlayerState()] + "\n";
	}
	return ret;
}

int NetworkServer::SearchByNick(std::string _nick)
{
	for (size_t i = 0; i < numPlayers; i++)
	{
		if (aClients[i].GetNick() == _nick)
		{
			return i;
		}
	}
	return -1;
}

int NetworkServer::GetNumDeads()
{
	int num = 0;
	for (size_t i = 0; i < numPlayers; i++)
	{
		if (aClients[i].GetPlayerState() == PLAYER_STATE_DEAD)
		{
			num++;
		}
	}
	return num;
}



NetworkServer::~NetworkServer()
{
}
