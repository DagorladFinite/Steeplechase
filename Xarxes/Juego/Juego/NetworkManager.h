#pragma once
#include <UDPSocket.h>
#include <time.h>
class NetworkManager
{
public:
	NetworkManager();
	NetworkManager(std::string _addressServer, std::string _addressClient, std::string _nick);
	~NetworkManager();

	void Send(std::string _message);
	int Receive(std::string& _message);

	void sendHello();
	void process(std::string _message);

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

