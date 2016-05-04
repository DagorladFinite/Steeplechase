#include "Game.h"


int main(int argc, char ** argv) {
	Game game("Catch the fire monsters", SCREEN_WIDTH, SCREEN_HEIGHT);

	try {
		game.run();
	}
	catch (std::exception e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
	}

	return 0;
}