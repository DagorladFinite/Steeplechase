#pragma once

//Third-party libraries
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>			//OpenGL Mathematics 
#include <iostream>
#include "GameConstants.h"
#include "SDLInterface.h"
#include "InputManager.h"
#include "Sprite.h"


/*
* The Game class manages the game execution
*/
class Game {
	public:						
		Game(std::string windowTitle, int screenWidth, int screenHeight);	//Constructor
		~Game();															//Destructor
		void run();															//Game execution	

	private:
			//Attributes	
		std::string _windowTitle;		//SDLInterface Title
		int _screenWidth;				//Screen width in pixels				
		int _screenHeight;				//Screen height in pixels				
		GameState _gameState;			//It describes the game state				
		SDLInterface _graphic;			//Manage the SDL graphic library		
		Sprite hero;
		Sprite fire;

			//Internal methods for the game execution
		void init();
		void gameLoop();		
		void executePlayerCommands();
		void doPhysics();
		void renderGame();
		void drawSprite(Sprite & e);
		
};

