#include "NetworkServer.h"

NetworkServer::NetworkServer(std::string _strServerAddress)
{

	SocketAddress saServer;
	saServer.SetAddress(_strServerAddress);
	//TODO: No se están controlando errores de Bind y NonBlocking
	udpSocket.Bind(saServer);
	udpSocket.NonBlocking(true);
	for (int i = 0; i < 4; i++)
	{
		playerList[i].connected = false;
	}


}


NetworkServer::~NetworkServer()
{
}

bool NetworkServer::Receive()
{
	bool exit = false;
	char buffer[1300];
	SocketAddress from;

	int numBytes = udpSocket.ReceiveFrom(buffer, 1300, from);
	if (numBytes > 0)
	{
		if (numBytes < 1300)
		{
			buffer[numBytes] = '\0';
		}
		//std::cout << "Recibo: " << buffer << std::endl;
		exit = processMessage(buffer, from);
	}
	return exit;
}

void NetworkServer::SendToAll(std::string _message)
{
	for (size_t i = 0; i < 4; i++)
	{
		if(playerList[i].connected == true)
			udpSocket.SendTo(_message.c_str(), _message.size(), playerList[i].GetSocketAddress());
	}
	
}

bool NetworkServer::processMessage(std::string _message, SocketAddress _saClient)
{

	int index_ = _message.find_first_of('_');
	std::string cabecera = _message.substr(0, index_);
	std::string contenido = _message.substr(index_ + 1, _message.size() - index_);
	int player = 0;

	for (int i = 0; i < 4; i++)
	{
		if (playerList[i].GetSocketAddress() == _saClient)
		{
			player = i;
		}
	}

	if (cabecera == "HELLO") {

		std::cout << "Hola!";
		playerList[playerlibre].SetNick(contenido);
		playerList[playerlibre].SetAddress(_saClient);
		playerList[playerlibre].connected = true;
		std::string welcome = "WELCOME";
		udpSocket.SendTo(welcome.c_str(), 1300, playerList[playerlibre].GetSocketAddress());
		playerlibre++;
	}

	if (cabecera == "POSITION") {
		std::cout << "Player: " + std::to_string(player) + " " + "Posicion anterior: " + contenido + "\n";
		std::string pos = "POSITION_";
		pos = pos.append("Ok");
		udpSocket.SendTo(pos.c_str(), 1300, _saClient);
	}

	if (cabecera == "ASKING") {
		std::cout << "Player: " + std::to_string(player) + " " + "Posicion preguntada: " + contenido + "\n";
		std::string pos = "ANSWER_";
		pos = pos.append("Ok");
		udpSocket.SendTo(pos.c_str(), 1300, _saClient);
	}



	return false;
}
