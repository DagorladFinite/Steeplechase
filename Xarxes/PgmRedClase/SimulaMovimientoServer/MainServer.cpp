#include <string>
#include <SocketTools.h>
#include "NetworkServer.h"

void ServerRun(std::string _serverAddress)
{
	bool exit;
	NetworkServer network(_serverAddress);
	do
	{
		exit = network.Receive();		
	} while (!exit);
}

void main(int args, char* argv[])
{
	std::string myAddress = argv[1];
	SocketTools::CargarLibreria();
	ServerRun(myAddress);
	SocketTools::DescargarLibreria();
}