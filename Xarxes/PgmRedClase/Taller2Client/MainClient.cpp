#pragma once
#include <SocketTools.h>
#include "UserInput.h"
#include "NetworkManager.h"
#include <thread>

void Client(std::string _addressServer, std::string _nick, UserData* _userData)
{
	NetworkManager networkManager(_addressServer, _nick, _userData);
	while (true)
	{
		//Paso 1:
		//Miro si he recibido algún mensaje del servidor
		//Si hay algún mensaje lo proceso con ProcessMessage
		//Tened en cuenta que si recibo 0 bytes, es porque el servidor ha cerrado la conexión
		//   y puedo salir del while(true)
		std::string message;
		int bytesReceived = networkManager.Receive(message);
		if (bytesReceived > 0)
		{
			networkManager.ProcessMessage(message);
		}
		else if (bytesReceived == 0)
		{
			break;
		}
		//Paso 2:
		//Miro si hay alguna palabra a enviar
		//Si la hay, la envío
		std::string word;
		bool enviar = _userData->GetWord(word);
		if (enviar)
		{
			//std::cout << "El usuario escribe " << word << std::endl;
			std::string strWordToSend = "WRITE_";
			strWordToSend = strWordToSend.append(word);
			networkManager.Send(strWordToSend.c_str());
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
	
	//Lanzamos el thread que captura la entrada de usuario
	UserInput userInput(&userData);
	std::thread tInput(userInput);
	tInput.detach();

	Client(addressServer, nick, &userData);
	SocketTools::DescargarLibreria();
	
	//Cerramos también el thread
	exit(0);
}