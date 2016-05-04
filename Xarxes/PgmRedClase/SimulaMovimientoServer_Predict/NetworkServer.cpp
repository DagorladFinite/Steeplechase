#include "NetworkServer.h"
#include "GameServerConstants.h"


NetworkServer::NetworkServer(std::string _strServerAddress)
{
	SocketAddress saServer;
	saServer.SetAddress(_strServerAddress);
	udpSocket.Bind(saServer);
	udpSocket.NonBlocking(true);
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		aPlayersConnected[i] = false;
	}
}

bool NetworkServer::Receive()
{
	bool exit = false;
	char buffer[MAX_BUFFER];
	SocketAddress from;

	int numBytes = udpSocket.ReceiveFrom(buffer, MAX_BUFFER, from);
	if (numBytes > 0)
	{
		if (numBytes < MAX_BUFFER)
		{
			buffer[numBytes] = '\0';
		}
		//std::cout << "Recibo: " << buffer << std::endl;
		exit = Dispatch_Message(buffer, from);
	}
	return exit;
}

void NetworkServer::SendToAll(std::string _message)
{
	for (size_t i = 0; i < MAX_PLAYERS; i++)
	{
		if (aPlayersConnected[i])
		{
			SocketAddress saClient = aPlayers[i].GetSocketAddress();
			//std::cout << "Envío a todos: " << _message.c_str() << std::endl;
			udpSocket.SendTo(_message.c_str(), _message.size(), saClient);
		}
	}
}

NetworkServer::~NetworkServer()
{

}

bool NetworkServer::Dispatch_Message(std::string _message, SocketAddress _saClient)
{
	int index_ = _message.find_first_of('_');
	std::string cabecera = _message.substr(0, index_);
	std::string contenido = _message.substr(index_ + 1, _message.size() - index_);

	ClientProxy cp(_saClient);
	int index = ExistClientProxy(cp);
	int freePosition = GetPositionFreePlayer();
	std::cout << "Llega: " << _message << std::endl;

	if (cabecera == HEADER_HELLO)
	{
		if (freePosition == -1)
		{
			std::string strMessage = HEADER_FULL;
			//std::cout << "Envío: " << strMessage.c_str() << std::endl;
			udpSocket.SendTo(strMessage.c_str(), strMessage.size(), _saClient);
		}
		else
		{
			if (index == -1)
			{
				cp.SetNick(contenido);
				aPlayers[freePosition] = cp;
				aPlayersConnected[freePosition] = true;
				std::string strMessage = HEADER_WELCOME;
				strMessage = strMessage.append("_");
				strMessage = strMessage.append(std::to_string(freePosition));
				//std::cout << "Envío: " << strMessage.c_str() << std::endl;
				udpSocket.SendTo(strMessage.c_str(), strMessage.size(), _saClient);

				int numPlayers = GetNumPlayers();
				if (numPlayers > 1)
				{
					for (int i = 0; i < MAX_PLAYERS; i++)
					{
						if (aPlayersConnected[i] && i != freePosition)
						{
							strMessage = std::string(HEADER_POSITION) + "_" + std::to_string(i) + ":" + std::to_string(aPlayers[i].GetPositionSquare());
							udpSocket.SendTo(strMessage.c_str(), strMessage.size(), _saClient);
						}
					}
				}
			}
		}
	}
	else if (cabecera == HEADER_TRYPOSITION)
	{
		if (index != -1)
		{
			int index_ = contenido.find_first_of('_');
			std::string strID = contenido.substr(0, index_);
			std::string deltaPosition = contenido.substr(index_ + 1, contenido.size() - index_);
			
			int tryPosition = atoi(deltaPosition.c_str());
			std::cout << "Intenta " << std::to_string(tryPosition) << std::endl;
			int newPosition = aPlayers[index].ChangeMove(tryPosition);
			std::cout << "Se concede " << std::to_string(newPosition) << std::endl;
			std::string strMessage = std::string(HEADER_POSITION) + "_" + strID + "_" + std::to_string(index) + ":" + std::to_string(newPosition);
			std::cout << "Envío: " << strMessage << std::endl;
			SendToAll(strMessage);
		}
	}
	else if (cabecera == HEADER_EXIT)
	{
		if (index != -1)
		{
			aPlayersConnected[index] = false;
			std::string strMessage = std::string(HEADER_POSITION) + "_-1_" + std::to_string(index) + ":" + std::to_string(MIN_SQUARE);
			SendToAll(strMessage);
		}
		if (GetNumPlayers() == 0)
		{
			return true;
		}
	}
	return false;
}

int NetworkServer::ExistClientProxy(ClientProxy _clientProxy)
{
	for (size_t i = 0; i < MAX_PLAYERS; i++)
	{
		if (aPlayersConnected[i] && aPlayers[i] == _clientProxy)
		{
			return i;
		}
	}
	return -1;
}

int NetworkServer::GetNumPlayers()
{
	int numPlayers = 0;
	for (size_t i = 0; i < MAX_PLAYERS; i++)
	{
		if (aPlayersConnected[i] == true)
		{
			numPlayers++;
		}
	}
	return numPlayers;
}

int NetworkServer::GetPositionFreePlayer()
{
	int numPlayers = GetNumPlayers();
	if (numPlayers < MAX_PLAYERS)
	{
		for (size_t i = 0; i < MAX_PLAYERS; i++)
		{
			if (!aPlayersConnected[i])
			{
				return i;
			}
		}
	}
	return -1;
}
