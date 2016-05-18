#pragma once
#include "ClientProxy.h"
#include <UDPSocket.h>
#include <time.h>
class NetworkServer
{
private:

	
	UDPSocket udpSocket;
	ClientProxy playerList[4];

	//Funciones que procesan los mensajes
	//Con strings
	bool processMessage(std::string _message, SocketAddress _saClient);
	//Serializado a nivel de bit (WOOOOOOOOOOWOWOWOWOWOWOWOWOW)
	bool processMessageBit(char* _message,int _size, SocketAddress _saClient);

	clock_t dispatchTime;


public:
	NetworkServer(std::string _strServerAddress);
	~NetworkServer();
	//Funciones que reciben tramas
	//Con strings
	bool Receive();
	//Serializado a nivel de bit (WOWOWOWOWOWOWOWOWOOOOOOOOOOOOOWOWOWOWOWOW)
	bool ReceiveBit();
	void SendToAll(std::string _message);
	void sendToAllChar(char*);

	void Dispatch();
	int playerlibre = 0;


	
};

