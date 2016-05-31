#include "NetworkManager.h"
#include "OutputMemoryStream.h"
#include "OutputMemoryBitStream.h"
#include "InputMemoryBitStream.h"
#include "InputMemoryStream.h"
#include "Constants.h"



NetworkManager::NetworkManager()
{
}


NetworkManager::NetworkManager(std::string _addressServer, std::string _addressClient, std::string _nick)
{
	saServer.SetAddress(_addressServer);
	SocketAddress myAddress;
	myAddress.SetAddress(_addressClient);
	int errBind = udpSocket.Bind(myAddress);
	int errBlock = udpSocket.NonBlocking(true);
	nick = _nick;
}



NetworkManager::~NetworkManager()
{
}

void NetworkManager::Send(std::string _message)
{
	//std::cout << "Envío: " << _message.c_str() << std::endl;
	udpSocket.SendTo(_message.c_str(), _message.length(), saServer);
}

void NetworkManager::SendBit(char* _message,int _size)
{
	//std::cout << "Envío: " << _message.c_str() << std::endl;
	udpSocket.SendTo(_message,_size, saServer);
}

bool NetworkManager::Start()
{
	return start;
}

int NetworkManager::Receive(std::string& _message)
{
	char buffer[1300];
	SocketAddress from;
	int bytesReceived = udpSocket.ReceiveFrom(buffer, 1300, from);
	if (bytesReceived > 0)
	{

		if (bytesReceived < 1300)
		{
			buffer[bytesReceived] = '\0';
		}
		_message = buffer;
	}
	process(_message);
	return bytesReceived;
}

int NetworkManager::ReceiveBit(std::string& _message)
{
	char buffer[1300];
	SocketAddress from;
	int bytesReceived = udpSocket.ReceiveFrom(buffer, 1300, from);
	if (bytesReceived > 0)
	{

		if (bytesReceived < 1300)
		{
			buffer[bytesReceived] = '\0';
		}
		_message = buffer;
	}
	processBit(buffer,bytesReceived);
	return bytesReceived;
}

void NetworkManager::sendHello() {

	if (status == 0) {

		clock_t time = clock();
		if (time > timeOfLastHello + 100)
		{
			std::string message = "HELLO";
			message = message.append("_" + nick);
			Send(message);
			timeOfLastHello = time;
		}
	}
}

void NetworkManager::sendHelloBit() {

	if (status == 0) {

		clock_t time = clock();
		if (time > timeOfLastHello + 100)
		{

			//Codifico a nivel de bit
			OutputMemoryBitStream ombs;

			//Tipo de paquete
			ombs.Write(PacketType::PT_HELLO, 3);

			//Nick
			ombs.WriteString(nick);

			//Envío
			SendBit(ombs.GetBufferPtr(),ombs.GetByteLength());
			std::cout << "Envío hello" << std::endl;

			//Pongo el timer a cero
			timeOfLastHello = time;
		}
	}
}

void NetworkManager::sendMove() {

	if (status == 1) {

		clock_t time = clock();
		if (time > sendTime + 100)
		{

			//Codifico a nivel de bit
			OutputMemoryBitStream ombs;

			//Tipo de paquete
			ombs.Write(PacketType::PT_MOVE, 3);

			//Número de veces que se ha pulsado spacebar
			ombs.Write(timesPressed, 2);

			//Posición del jugador antes del movimiento
			//Enviamos esta información para corregir los problemas que pueda dar la pérdida de paquetes

			
			ombs.Write(playerPrevPositions[playerNumber], 10);

			//Envío
			SendBit(ombs.GetBufferPtr(), ombs.GetByteLength());
			//std::cout << "Envío el número de veces que he pulsado"<< timesPressed << std::endl;
			
			//Pongo el contador de inputs a cero
			timesPressed = 0;

			//Pongo el timer a cero
			sendTime = time;
		}
	}

}

void NetworkManager::process(std::string _message) {

	int index_ = _message.find_first_of('_');
	std::string cabecera = _message.substr(0, index_);
	std::string contenido = _message.substr(index_ + 1, _message.size() - index_);

	if (_message == "WELCOME") {

		std::cout << "Me han oído";
		
		status = 1;
	}
	if (cabecera == "POSITION") {

		std::cout << "Ok\n";
		status = 1;
	}

	if (cabecera == "ANSWER") {

		std::cout << "Respuesta\n";
		status = 1;
	}
}

void NetworkManager::processBit(char* _message, int _size) {

	InputMemoryBitStream imbs(_message, _size * 8);
	PacketType pt = PacketType::PT_EMPTY;
	imbs.Read(&pt, 3);

	if (pt == PacketType::PT_WELCOME) {

		imbs.Read(&playerNumber, 2);
		std::cout << playerNumber;
		std::cout << "Me han oido!";
		start = true;
		status = 1;
	}
	else if (pt == PacketType::PT_AUTHOR) {

		//std::cout << "Posición del jugador 1: "<< std::endl;
		imbs.Read(&playerPositions[0], 10);
		//std::cout << &playerPositions[0];

		//std::cout << "Posición del jugador 2: " << std::endl;
		imbs.Read(&playerPositions[1], 10);
		//std::cout << &playerPositions[1];

		//std::cout << "Posición del jugador 3: " << std::endl;
		imbs.Read(&playerPositions[2], 10);
		//std::cout << &playerPositions[2];

		//std::cout << "Posición del jugador 4: " << std::endl;
		imbs.Read(&playerPositions[3], 10);
		//std::cout << &playerPositions[3];

	}
  	else if (pt == PacketType::PT_FINISH) {
		imbs.Read(&winner, 2);
		if (winner == playerNumber)
		{
			std::cout << std::endl << "You won, congratulations!:"<<std::endl;
		}
		else {
			std::cout << std::endl << "You lost! The winner is: Player " << winner << std::endl;
		}
		
	}
	
}