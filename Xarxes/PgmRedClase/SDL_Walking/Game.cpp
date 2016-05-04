#include "Game.h"
/**
* Constructor
* Tip: You can use an initialization list to set its attributes
* @param windowTitle is the window title
* @param screenWidth is the window width
* @param screenHeight is the window height
*/
Game::Game(std::string windowTitle, int screenWidth, int screenHeight) :
	_windowTitle(windowTitle),
	_screenWidth(screenWidth),
	_screenHeight(screenHeight),
	_gameState(GameState::INIT),
	_mouseIsPressed(false),
	_mouseCoords(_graphic.getMouseCoords()) {
}

/**
* Destructor
*/
Game::~Game()
{
}

/*
* Game execution
*/
void Game::run() {
		//Prepare the game components
	init();
		//Start the game if everything is ready
	gameLoop();
}

/*
* Initialize all the components
*/
void Game::init() {
	srand((unsigned int)time(NULL));
		//Create a window
	_graphic.createWindow(_windowTitle, _screenWidth, _screenHeight, false);	
	_graphic.setWindowBackgroundColor(255, 255, 255, 255);
		//Load the sprites associated to the different game elements
	_graphic.loadTexture(SPRITE_HERO, "../sharedResources/images/characters/hero.png");
	_graphic.loadTexture(SPRITE_FIRE, "../sharedResources/images/characters/fireSprite.png");

	_graphic.loadTexture(SPRITE_MENU, "../sharedResources/images/interface/menu.png");
	_graphic.loadTexture(SPRITE_START_MENU, "../sharedResources/images/interface/start_menu.png");
	_graphic.loadTexture(SPRITE_BUTTON_NEWGAME, "../sharedResources/images/interface/new_game.png");
	_graphic.loadTexture(SPRITE_BUTTON_OPTIONS, "../sharedResources/images/interface/options.png");
	_graphic.loadTexture(SPRITE_BUTTON_RESUME, "../sharedResources/images/interface/resume_game.png");
	_graphic.loadTexture(SPRITE_BUTTON_EXIT, "../sharedResources/images/interface/exit_game.png");
	_graphic.loadTexture(SPRITE_LIVES, "../sharedResources/images/interface/lives.png");

	_graphic.loadTexture(SPRITE_TERRAIN_GRASS_ALL, "../sharedResources/images/terrain/grass1.png");
	_graphic.loadTexture(SPRITE_TERRAIN_ROAD_HOROZONTAL, "../sharedResources/images/terrain/roadh.png");
	_graphic.loadTexture(SPRITE_TERRAIN_ROAD_VERTICAL, "../sharedResources/images/terrain/roadv.png");
	_graphic.loadTexture(SPRITE_TERRAIN_DIRT, "../sharedResources/images/terrain/dirt.png");

	_graphic.loadTexture(SPRITE_TERRAIN_DIRT_B, "../sharedResources/images/terrain/dirtb.png");
	_graphic.loadTexture(SPRITE_TERRAIN_DIRT_T, "../sharedResources/images/terrain/dirtt.png");
	_graphic.loadTexture(SPRITE_TERRAIN_DIRT_L, "../sharedResources/images/terrain/dirtl.png");
	_graphic.loadTexture(SPRITE_TERRAIN_DIRT_R, "../sharedResources/images/terrain/dirtr.png");
	_graphic.loadTexture(SPRITE_TERRAIN_DIRT_OBR, "../sharedResources/images/terrain/dirtobr.png");
	_graphic.loadTexture(SPRITE_TERRAIN_DIRT_OBL, "../sharedResources/images/terrain/dirtobl.png");
	_graphic.loadTexture(SPRITE_TERRAIN_DIRT_OTR, "../sharedResources/images/terrain/dirtotr.png");
	_graphic.loadTexture(SPRITE_TERRAIN_DIRT_OTL, "../sharedResources/images/terrain/dirtotl.png");
		//Set the font style
	_graphic.setFontStyle(TTF_STYLE_NORMAL);
		//Initialize the game elements
	//_hero.initialize();
		//The counter used to manage the score
	_lastTimeSpritesWereUpdated = clock();
		//Init terrains and map
	//loadTerrains();
	_map.init();
		//int ** ter= _terrains.getTerrain(1);
		//_map.setMap(ter);
	_map.setSDLInterface(_graphic);
}


/*
* Game execution: Gets input events, processes game logic and draws sprites on the screen
*/
void Game::gameLoop() {	
	_gameState = GameState::START;

	while (_gameState != GameState::EXIT) {		
			//Detect keyboard and/or mouse events
		_graphic.detectInputEvents();
			//Execute the player commands 
		executePlayerCommands();
			//Update the game physics
		doPhysics();
			//Render game
		renderGame();			
	}
}

/**
* Executes the actions sent by the user by means of the keyboard and mouse
* Reserved keys:
- up | left | right | down moves the player object
- m opens the menu
*/
void Game::executePlayerCommands() {
	// Gets the coordinates of the mouse
	_mouseCoords = _graphic.getMouseCoords();
	//Detects if the player clicks, needs to be improved to a better system to detect the unclick more accurately
	if (_graphic.isKeyPressed(SDL_BUTTON_LEFT)) {
		_mouseIsPressed = true;
	}
	else {
		_mouseIsPressed = false;
	}

	// Depending on the gamestate, the inputs change
	switch (_gameState) {
		case GameState::PLAY:
			//Opens menu
			if (_graphic.isKeyPressed(SDLK_ESCAPE)) {
				_gameState = GameState::MENU;
			}

			if (_graphic.isKeyDown(SDLK_UP)) {
				_hero.setMovementUp();
				_hero.setMoving(true);
				if (_hero.getYAtWorld() > 64)_hero.move(0, - PLAYER_SPEED);
				else _map.move(0, PLAYER_SPEED);
			}

			if (_graphic.isKeyDown(SDLK_DOWN)) {
				_hero.setMovementDown();
				_hero.setMoving(true);
				if (_hero.getYAtWorld() < (700 - (64*2)))_hero.move(0, PLAYER_SPEED);
				else _map.move(0, -PLAYER_SPEED);
			}

			if (_graphic.isKeyDown(SDLK_LEFT)) {
				_hero.setMovementLeft();
				_hero.setMoving(true);
				if (_hero.getXAtWorld() > 64) _hero.move(-PLAYER_SPEED, 0);
				else _map.move(PLAYER_SPEED, 0);
			}

			if (_graphic.isKeyDown(SDLK_RIGHT)) {
				_hero.setMovementRight();
				_hero.setMoving(true);
				if (_hero.getXAtWorld() < (700 - (64 * 2))) _hero.move(PLAYER_SPEED, 0);
				else _map.move(-PLAYER_SPEED, 0);
			}

			break;
		case GameState::MENU:
			if (_graphic.isKeyPressed(SDLK_ESCAPE)) {
				_gameState = GameState::PLAY;
			}
			break;
		}
}

/*
* Execute the game physics
*/
void Game::doPhysics() {
	switch (_gameState) {
		case GameState::PLAY:
			_hero.nextAnimationFrame(_graphic.getCurrentTicks());
			if (_hero.isMoving()) _hero.setMoving(false);
			break;
		//MENU and START check if anybutton is pressed or highlighted
		case GameState::MENU:
			_menu.checkIfMouseisOverButton(_mouseCoords);
			_gameState = _menu.checkIfButtonIsPressed(_mouseIsPressed,_mouseCoords);
			break;
		case GameState::START:
			_startMenu.checkIfMouseisOverButton(_mouseCoords);
			_gameState = _startMenu.checkIfButtonIsPressed(_mouseIsPressed,_mouseCoords);
			if (_gameState == GameState::PLAY) {
				//CALL  RESET GAME
			}
			break;
	}
}

/**
* Render the game on the screen
*/
void Game::renderGame() {
		//Draw the screen's content based on the game state
	switch (_gameState) {
		case GameState::PLAY:
			_graphic.clearWindow();
			drawGame();
			break;
		case GameState::MENU:
			drawMenu();
			break;
		case GameState::START:
			drawStartMenu();
			break;
	}
		//Refresh screen
	_graphic.refreshWindow();
}

/*
* Draw the start menu
*/
void Game::drawStartMenu() {
	_graphic.drawTexture(_startMenu.getMenuSpriteID(), 0, 0, 700, 700, 0, 0 ,700, 700);
	drawButton(_startMenu.getNewGameSprite());
	drawButton(_startMenu.getExitSprite());
}

/*
* Draw the game menu
*/
void Game::drawMenu() {
	_graphic.drawTexture(_menu.getMenuSpriteID(), 0, 0, 440, 390,130, 155, 440, 390);
	drawButton(_menu.getOptionsSprite());
	drawButton(_menu.getResumaSprite());
	drawButton(_menu.getExitSprite());
}

/*
* Draw the game, winner or loser screen
*/
void Game::drawGame()	{
	_map.renderMap();
	drawSprite(_hero.getHeroSprite());
	drawSprite(_hero.getLivesSprite());
}

/*
* Draw the sprite on the screen
* @param sprite is the sprite to be displayed
*/
void Game::drawSprite(Sprite & sprite) {
	_graphic.drawTexture(sprite.getSpriteId(), sprite.getWidth() * sprite.getCurrentFrame(), sprite.getHeight() * sprite.getCurrentVerticalFrame(), sprite.getWidth(), sprite.getHeight()
		, sprite.getXAtWorld(), sprite.getYAtWorld(), sprite.getWidth(), sprite.getHeight());
}

/*
* Draw the button on the screen
* @param button is the sprite to be displayed
*/
void Game::drawButton(Sprite &sprite) {
	_graphic.drawTexture(sprite.getSpriteId(), MENU_BUTTON_DEFAULT_WIDTH*sprite.getCurrentFrame(), 0, MENU_BUTTON_DEFAULT_WIDTH, MENU_BUTTON_DEFAULT_HEIGHT
		, sprite.getXAtWorld(), sprite.getYAtWorld(), MENU_BUTTON_DEFAULT_WIDTH, MENU_BUTTON_DEFAULT_HEIGHT);
}

/*
void Game::loadTerrains() {
	int * *ter = 0;
	ter = new int*[MAP_COLUMS];

	for (int i = 0; i < MAP_COLUMS; i++) {
		ter[i] = new int[MAP_ROWS];
		for (int j = 0; j < MAP_ROWS; j++) {
			ter[i][j] = SPRITE_TERRAIN_DIRT;
			int i = 0;
		}
	}

	_terrains.setNewTerrain(ter);
}	  */