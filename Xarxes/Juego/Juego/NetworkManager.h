#pragma once
#include <UDPSocket.h>
#include <time.h>


class NetworkManager
{
public:
	NetworkManager();
	NetworkManager(std::string _addressServer, std::string _addressClient, std::string _nick);
	~NetworkManager();

	//Funci�n de recepci�n
	//Recibe strings
	int Receive(std::string& _message);
	int ReceiveBit(std::string& _message);
	

	//Funciones de env�o de tramas
	//Env�a una trama que nosotros decidamos
	void Send(std::string _message);

	void SendBit(char* _message,int _size);


	//Env�a los HELLO para conectarse al servidor
	//Con strings
	void sendHello();
	//Serializado a nivel de bit (WOOOOOOOOOOW)
	void sendHelloBit();

	//Env�a el n�mero de veces que me he movido al servidor
	void sendMove();

	//Funciones que procesan los mensajes
	//Con strings
	void process(std::string _message);
	//Serializado a nivel de bit (WOOOOOOOOOOOOOOOOOWOWOWOWOW)
	void processBit(char* _message,int _size);

	int playerNumber;
	int timesPressed;

private:
	UDPSocket udpSocket;
	SocketAddress saServer;
	std::string nick;
	int playerId;
	clock_t timeOfLastHello;
	clock_t sendTime;

	//LEYENDA:
	//0 NO CONECTADO
	//1 CONECTADO
	int status = 0;
};

