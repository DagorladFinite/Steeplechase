#include "Server.h"
#include "GameConstantsServer.h"
#include <string>


Server::Server(std::string _serverAddress)
{
	//TODO: Inicializa el UDPSocket
}



void Server::LoadingPlayers()
{
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		//TODO: Esperar a que lleguen tantos jugadores como se indican en NUM_PLAYERS.
		//TODO: Cuando llegue el HELLO hemos de comprobar si ya tenemos guardada la direcci�n de este cliente o no.
		//TODO: Si ya la tenemos guardada, s�lo le volvemos a enviar el WELCOME.
		//TODO: Si no la tenemos guardada, a�adimos el client proxy con la informaci�n necesaria y tambi�n enviamos el WELCOME.
		//TODO: Recordad que con el HELLO llega el nick, que tenemos que guardar en el client proxy tambi�n.
		
	}
	
}

int Server::Send(std::string _message, SocketAddress& _address)
{
	//TODO: Enviar el mensaje a esta direcci�n concreta
	return 0;
}

void Server::SendToAll(std::string _message)
{
	for (size_t i = 0; i < aPlayers.size(); i++)
	{
		//TODO: Enviar el mensaje a todos los jugadores
		
	}
}

int Server::Receive(std::string& _message)
{
	_message = "";
	//TODO: Recibir mensajes a trav�s del UDPSocket
	//TODO: si no hay nada que recibir se retorna 0 y no se copia nada en el _message
	//TODO: Si hay datos que recibir, se pone en el return en n�mero que bytes que han llegado y el mensaje en _message
	return 0;
}

void Server::NonBlocking(bool _ok)
{
	udpSocket.NonBlocking(_ok);
	
}


Server::~Server()
{
}
