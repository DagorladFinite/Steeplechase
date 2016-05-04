#include "Game.h"
#include <SocketTools.h>
#include <UDPSocket.h>


void Launch(std::string _serverAddress, std::string _clientAddress, std::string _nick)
{
	Game game("Catch the fire monsters", SCREEN_WIDTH, SCREEN_HEIGHT, _serverAddress, _clientAddress, _nick);

	try {
		game.run();
	}
	catch (std::exception e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
	}
}

int main(int argc, char ** argv) {
	SocketTools::CargarLibreria();
	std::string serverAddress = argv[1];
	std::string clientAddress = argv[2];
	std::string nick = argv[3];
	
	Launch(serverAddress, clientAddress, nick);

	SocketTools::DescargarLibreria();
	return 0;
}