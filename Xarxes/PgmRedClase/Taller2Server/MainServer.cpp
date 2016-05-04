#pragma once
#include <SocketTools.h>
#include "Server.h"

void ServerRun(std::string _serverAddress, int _numPlayers)
{
	Server server(_serverAddress, _numPlayers);
	server.LoadingPlayers(_numPlayers);

	while (true)
	{
		server.ReceiveAndProcessMsgClients();

		bool exit = server.SendWord();
		if (exit)
		{
			break;
		}
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