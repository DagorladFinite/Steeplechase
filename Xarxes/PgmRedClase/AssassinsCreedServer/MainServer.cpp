#pragma once
#include <SocketTools.h>
#include "NetworkServer.h"

void ServerRun(std::string _serverAddress, int _numPlayers)
{
	NetworkServer server(_serverAddress, _numPlayers);
	server.LoadingPlayers();

	while (true)
	{
		bool exit = server.ReceiveAndProcessMsgClients();

		if (exit)
			break;
	}

}

void main(int args, char* argv[])
{
	std::string myAddress = argv[1];
	int numPlayers = atoi(argv[2]);

	SocketTools::CargarLibreria();
	ServerRun(myAddress, numPlayers);
	SocketTools::DescargarLibreria();
}