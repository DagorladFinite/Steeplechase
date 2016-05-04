#include "Game.h"
#include <SocketTools.h>


int main(int args, char* argv[]) {
	std::string to = argv[1];
	std::string me = argv[2];
	std::string nick = argv[3];

	SocketTools::CargarLibreria();
	Game game("Basic game engine", 700, 700, to,me,nick);

	try {
		game.run();
	}
	catch (std::exception e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
	}

	return 0;
}