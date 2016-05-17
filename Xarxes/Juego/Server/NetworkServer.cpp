#include "NetworkServer.h"
#include "OutputMemoryStream.h"
#include "OutputMemoryBitStream.h"
#include "InputMemoryBitStream.h"
#include "InputMemoryStream.h"
#include "Constants.h"

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

bool NetworkServer::ReceiveBit()
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
		exit = processMessageBit(buffer,numBytes, from);
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

bool NetworkServer::processMessageBit(char* _message,int _size, SocketAddress _saClient)
{


	InputMemoryBitStream imbs(_message, _size * 8);
	PacketType pt = PacketType::PT_EMPTY;
	imbs.Read(&pt, 3);
	int player = 0;

	for (int i = 0; i < 4; i++)
	{
		if (playerList[i].GetSocketAddress() == _saClient)
		{
			player = i;
		}
	}

	if (pt == PacketType::PT_HELLO) {

		std::cout << "Hola!";
		std::string nick;
		imbs.ReadString(&nick);
		playerList[playerlibre].SetNick(nick);
		playerList[playerlibre].SetAddress(_saClient);
		playerList[playerlibre].connected = true;
		OutputMemoryBitStream ombs;
		ombs.Write(PacketType::PT_WELCOME, 3);
		ombs.Write(player, 2);
		udpSocket.SendTo(ombs.GetBufferPtr(), 1300, playerList[playerlibre].GetSocketAddress());
		playerlibre++;
	}

	if (pt == PacketType::PT_MOVE) {

		std::cout << "Me ha llegado una petición de movimiento."<< std::endl;;
		int toMove = 0;
		imbs.Read(&toMove, 2);

		playerList[player].position = playerList[player].position + (3 * toMove);
		std::cout << "El jugador se ha movido a la posición: " << playerList[player].position << std::endl;
		

	}

	return false;
}

void NetworkServer::Dispatch(){

	clock_t time = clock();
	if (time > dispatchTime + 125)
	{
		OutputMemoryBitStream ombs;
		ombs.Write(PacketType::PT_MOVE, 3);
		ombs.Write(timesPressed, 2);
		SendBit(ombs.GetBufferPtr(), ombs.GetByteLength());
		std::cout << "Envío el número de veces que he pulsado" << timesPressed << std::endl;
		timesPressed = 0;
		sendTime = time;
	}


}