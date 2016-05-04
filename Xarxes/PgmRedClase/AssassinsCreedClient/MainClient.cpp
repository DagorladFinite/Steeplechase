#pragma once
#include <string>
#include <SocketTools.h>
#include <TCPSocket.h>
#include <exception>
#include "UserInput.h"
#include "NetworkClient.h"
#include <thread>

void Client(std::string _addressServer, std::string _nick, UserData* _userData)
{
	NetworkClient network(_addressServer, _nick, _userData);
	while (true)
	{
		std::string message;
		int bytesReceived = network.Receive(message);
		if (bytesReceived > 0)
		{
			network.ProcessMessage(message);
		}
		else if (bytesReceived == 0)
		{
			break;
		}

		std::string msg;
		bool enviar = _userData->Get_Message(msg);
		if (enviar)
		{
			network.Send(msg.c_str());
		}
	}
	std::cout << "Salgo del while true" << std::endl;
}

void main(int args, char* argv[])
{
	std::string addressServer = argv[1];
	std::string nick = argv[2];

	SocketTools::CargarLibreria();
	UserData userData;
	UserInput userInput(&userData);
	std::thread tInput(userInput);
	tInput.detach();

	Client(addressServer, nick, &userData);
	SocketTools::DescargarLibreria();
	exit(0);
}