#include "Network.h"



Network::Network(std::string _addressServer, std::string _addressClient, std::string _nick): nick(_nick), networkState(NetworkClientState::NCS_Uninitialized)
{
	//TODO: Inicializamos el socket de cliente y lo ponemos a nonblocking.
	//TODO: Nos tenemos que guardar la dirección del servidor para podernos comunicar con él.
	
}

void Network::Send(std::string _message)
{
	//TODO: Enviamos este mensaje a servidor
}

int Network::Receive(std::string& _message)
{
	//TODO: Recibir a través del UDPSocket. Sólo deberían llegarnos datos de servidor.
	//TODO: Si no llegan datos, retornamos 0 y no copiamos nada en _message.
	//TODO: Si llegan datos, retornamos el número de bytes que han llegado y copiamos en _message
	
	
	return 0;
}

void Network::NonBlocking(bool _ok)
{
	udpSocket.NonBlocking(_ok);
}



NetworkClientState Network::GetState()
{
	return networkState;
}

void Network::SetState(NetworkClientState _state)
{
	networkState = _state;
}

void Network::SayHello()
{
	if (networkState == NetworkClientState::NCS_Welcomed)
	{
		return;
	}
	if (networkState == NetworkClientState::NCS_Uninitialized)
	{
		networkState = NetworkClientState::NCS_SayingHello;
	}
	
	clock_t time = clock();
	if (time > mTimeOfLastHello + FREQUENCY_SAYING_HELLO)
	{
		networkState = NetworkClientState::NCS_SayingHello;
		std::string message = HEADER_HELLO;
		message = message.append(nick);
		Send(message);
		mTimeOfLastHello = time;
	}
}

void Network::ProcessWelcome()
{
	networkState = NetworkClientState::NCS_Welcomed;
}

void Network::ProcessMonsters(ListOfMonsters & _listOfMonsters, std::string _strMonsters)
{
	_listOfMonsters.Deserialize(_strMonsters);
}


Network::~Network()
{
	
}
