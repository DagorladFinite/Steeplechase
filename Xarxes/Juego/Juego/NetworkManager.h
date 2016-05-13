#pragma once
#include <UDPSocket.h>
#include <time.h>


class NetworkManager
{
public:
	NetworkManager();
	NetworkManager(std::string _addressServer, std::string _addressClient, std::string _nick);
	~NetworkManager();

	//Función de recepción
	//Recibe strings
	int Receive(std::string& _message);
	int ReceiveBit(std::string& _message);
	

	//Funciones de envío de tramas
	//Envía una trama que nosotros decidamos
	void Send(std::string _message);

	//Envía los HELLO para conectarse al servidor
	//Con strings
	void sendHello();
	//Serializado a nivel de bit (WOOOOOOOOOOW)
	void sendHelloBit();

	//Funciones que procesan los mensajes
	//Con strings
	void process(std::string _message);
	//Serializado a nivel de bit (WOOOOOOOOOOOOOOOOOWOWOWOWOW)
	void processBit(char* _message,int _size);

private:
	UDPSocket udpSocket;
	SocketAddress saServer;
	std::string nick;
	int playerId;
	clock_t timeOfLastHello;
	clock_t timeOfLastMove;

	//LEYENDA:
	//0 NO CONECTADO
	//1 CONECTADO
	int status = 0;
};

