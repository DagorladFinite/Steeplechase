#pragma once

//Third-party libraries
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>			//OpenGL Mathematics 
#include <iostream>
#include <time.h>
#include "GameConstants.h"
#include "SDLInterface.h"
#include "InputManager.h"
#include "Sprite.h"
#include "Menu.h"
#include "Button.h"
#include "StartMenu.h"
#include "Map.h"
#include "Terrains.h"
#include "Hero.h"


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
		std::string _windowTitle;			//SDLInterface Title
		int _screenWidth;					//Screen width in pixels				
		int _screenHeight;					//Screen height in pixels				
		GameState _gameState;				//It describes the game state				
		SDLInterface _graphic;				//Manage the SDL graphic library		
		int _lastTimeSpritesWereUpdated;	//Counter to compute the time
		Hero _hero;
		
		Menu _menu;
		StartMenu _startMenu;
		bool _mouseIsPressed;
		glm::ivec2 _mouseCoords;

		Map _map;
		Terrains _terrains;

		//Internal methods for the game execution
		void init();
		void gameLoop();		
		void executePlayerCommands();
		void doPhysics();
		void renderGame();
		void drawStartMenu();
		void drawMenu();
		void drawGame();
		void drawSprite(Sprite & e);
		void drawButton(Sprite &e);
		//void loadTerrains();
};

