#pragma once

//Third-party libraries
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>			//OpenGL Mathematics 
#include <iostream>
#include <time.h>
#include <GameConstants.h>
#include "SDLInterface.h"
#include "InputManager.h"
#include "Sprite.h"
#include "ListOfMonsters.h"
#include "Network.h"


/*
* The Game class manages the game execution
*/
class Game {
	public:						
		Game(std::string windowTitle, int screenWidth, int screenHeight, std::string serverAddress, std::string clientAddress, std::string nick);	//Constructor
		~Game();															//Destructor
		void run();															//Game execution	
		
	private:
			//Attributes	
		std::string _windowTitle;		//SDLInterface Title
		int _screenWidth;				//Screen width in pixels				
		int _screenHeight;				//Screen height in pixels				
		GameState _gameState;			//It describes the game state				
		SDLInterface _graphic;			//Manage the SDL graphic library		
		ListOfMonsters _monsters;		//It manages the data regarding to the monsters
		Network _network;
		clock_t _initTimePlaying;
		

			//Internal methods for the game execution
		void init();
		void Receiving();
		void gameLoop();		
		void executePlayerCommands();
		void doPhysics();
		void renderGame();
		void drawMenu();
		void drawInitInfo();
		void drawGame();
		void drawSprite(Sprite & e);		
};

