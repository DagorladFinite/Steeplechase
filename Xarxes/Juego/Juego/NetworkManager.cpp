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

}



NetworkManager::~NetworkManager()
{
}

void NetworkManager::Send(std::string _message)
{
	//std::cout << "Envío: " << _message.c_str() << std::endl;
	udpSocket.SendTo(_message.c_str(), _message.length(), saServer);
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
			OutputMemoryBitStream ombs;
			ombs.Write(PacketType::PT_HELLO, 3);
			ombs.WriteString(nick);
			Send(ombs.GetBufferPtr());
			std::cout << "Envío hello" << std::endl;
			timeOfLastHello = time;
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

		std::cout << "Me han oido!";
		status = 1;
	}
	
}