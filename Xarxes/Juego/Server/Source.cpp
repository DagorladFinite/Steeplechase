#pragma once
#include <SocketTools.h>
#include "NetworkServer.h"
#include <time.h>


void main(int args, char* argv[]) {
	std::string myAddress = argv[1];
	SocketTools::CargarLibreria();
	NetworkServer network(myAddress);

	srand(time(NULL));
	while (true)
	{

		//Recibimos y procesamos
		network.ReceiveBit();

		//Pérdida de paquetes. 
		//Tenemos un 1% de posibilidades de que "el paquete no llegue"
		int pickedChoice = (int)(rand() % 100) + 1;

		network.CheaterBuster();

		if (pickedChoice > 1) {
			network.Dispatch();
			network.newInfo = false;
		}

	
	}
	SocketTools::DescargarLibreria();
	
	
}