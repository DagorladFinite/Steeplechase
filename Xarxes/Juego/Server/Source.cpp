#pragma once
#include <SocketTools.h>
#include "NetworkServer.h"


void main(int args, char* argv[]) {
	std::string myAddress = argv[1];
	SocketTools::CargarLibreria();
	NetworkServer network(myAddress);
	while (true)
	{

		
		network.ReceiveBit();

	
	}
	SocketTools::DescargarLibreria();
	
	
}