#include "NetworkServer.h"
#include "GameServerConstants.h"


NetworkServer::NetworkServer(std::string _strServerAddress)
{
	SocketAddress saServer;
	saServer.SetAddress(_strServerAddress);
	//TODO: No se están controlando errores de Bind y NonBlocking
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

	if (cabecera == std::string(HEADER_HELLO))
	{
		if (freePosition == -1 && index == -1)
		{
			//Si no hay ninguna posición del array de clientes vacío y es un jugador nuevo, este jugador "no cabe".
			std::string strMessage = HEADER_FULL;
			udpSocket.SendTo(strMessage.c_str(), strMessage.size(), _saClient);
		}
		else if (index > 0)
		{
			//Aunque no hay posiciones libres solicita WELCOME un jugador que ya tengo en la lista (no le ha llegado antes)
			//Se lo vuelvo a enviar
			std::string strMessage = std::string(HEADER_WELCOME)+"_"+ std::to_string(index);
			udpSocket.SendTo(strMessage.c_str(), strMessage.size(), _saClient);
		}
		else if (freePosition > -1 && index == -1 )
		{
			//Es un jugador nuevo y hay sitio para él.
			//Le doy la bienvenida
			std::string strMessage = std::string(HEADER_WELCOME) + "_" + std::to_string(freePosition);
			udpSocket.SendTo(strMessage.c_str(), strMessage.size(), _saClient);
			
			//Me guardo el jugador
			cp.SetNick(contenido);
			aPlayers[freePosition] = cp;
			aPlayersConnected[freePosition] = true;
			
			//Si hay otros jugadores conectados además de él mismo, le envío al jugador que acaba de llegar la
			//posición del resto de jugadores
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
	else if (cabecera == std::string(HEADER_TRYPOSITION))
	{
		//Sólo lo proceso si me llega de un jugador que tengo "registrado"
		if (index != -1)
		{
			int tryPosition = atoi(contenido.c_str());
			std::cout << "Intenta " << std::to_string(tryPosition) << std::endl;
			//Esta función valida si el movimiento es correcto. Me da la posición en la que debe quedar el cuadrado.
			int newPosition = aPlayers[index].ChangeMove(tryPosition);
			std::cout << "Se concede " << std::to_string(newPosition) << std::endl;
			//Reenvío a todos los jugadores donde queda este cuadrado (incluido el que lo solicitó)
			std::string strMessage = std::string(HEADER_POSITION)+"_" + std::to_string(index) + ":" + std::to_string(newPosition);
			SendToAll(strMessage);
		}
	}
	else if (cabecera == std::string(HEADER_EXIT))
	{
		//Se desconecta uno de los jugadores. Libero su posición.
		//Reseteo la posición del cuadrado en el resto de jugadores.
		if (index != -1)
		{
			aPlayersConnected[index] = false;
			std::string strMessage = std::string(HEADER_POSITION) + std::to_string(index) + ":" + std::to_string(MIN_SQUARE);
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
