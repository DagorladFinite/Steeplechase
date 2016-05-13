#include "Game.h"



/**
* Constructor
* Tip: You can use an initialization list to set its attributes
* @param windowTitle is the window title
* @param screenWidth is the window width
* @param screenHeight is the window height
*/
Game::Game(std::string windowTitle, int screenWidth, int screenHeight,std::string to, std::string me,std::string nick):
	_windowTitle(windowTitle),
	_screenWidth(screenWidth),
	_screenHeight(screenHeight),
	_gameState(GameState::INIT),
	network(to,me,nick)
	{
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
		//Create a window
	_graphic.createWindow(_windowTitle, _screenWidth, _screenHeight, false);	
	_graphic.setWindowBackgroundColor(0, 0, 0, 255);
		//Load the sprites associated to the different game elements
	_graphic.loadTexture(SPRITE_HERO, "../sharedResources/images/characters/hero.png");
	_graphic.loadTexture(SPRITE_FIRE, "../sharedResources/images/characters/fireSprite.png");
		//Set the font style
	_graphic.setFontStyle(TTF_STYLE_NORMAL);
		//Initialize the game elements
	hero.setInitialValues(10, 75, SPRITE_HERO, 0, 4);
	hero2.setInitialValues(10,225, SPRITE_HERO, 0, 4);
	hero3.setInitialValues(10, 375, SPRITE_HERO, 0, 4);
	hero4.setInitialValues(10, 525, SPRITE_HERO, 0, 4);
	fire.setInitialValues(100, 100, SPRITE_FIRE, 0, 5);

	//network.initialize()
}


/*
* Game execution: Gets input events, processes game logic and draws sprites on the screen
*/
void Game::gameLoop() {	
	_gameState = GameState::PLAY;

	while (_gameState != GameState::EXIT) {		

		//Enviamos señales
		std::string message;
		network.sendHelloBit();

		network.ReceiveBit(message);
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

	if (_graphic.isKeyPressed(SDL_BUTTON_LEFT)){
		glm::ivec2 mouseCoords = _graphic.getMouseCoords();
		std::cout << "Screen (" << mouseCoords.x << ", " << mouseCoords.y << ")"<< std::endl;
	}

	if (_graphic.isKeyDown(SDLK_UP)) {
		
	}

	if (_graphic.isKeyDown(SDLK_LEFT)) {
		
	}
	if (_graphic.isKeyDown(SDLK_DOWN)) {
		
	}

	if (_graphic.isKeyDown(SDLK_RIGHT)) {
		
	}

	if (_graphic.isKeyPressed(SDLK_SPACE)) {

		/*if (hero.getXAtWorld() < 640) {
			std::string msg = "POSITION_";
			std::string pos = std::to_string(hero.getXAtWorld());
			msg = msg.append(pos);
			network.Send(msg);

			std::string ask = "ASKING_";
			std::string pos2 = std::to_string(hero.getXAtWorld() + 3);
			ask = ask.append(pos2);
			network.Send(ask);

			hero.setPositionAtWorld(hero.getXAtWorld() + 3, hero.getYAtWorld());
		}*/
	}

	if (_graphic.isKeyPressed(SDLK_m)) {
		std::cout << "Menu" << std::endl;
	}

	if (_graphic.isKeyPressed(SDLK_ESCAPE)) {
		_gameState = GameState::EXIT;
	}
}

/*
* Execute the game physics
*/
void Game::doPhysics() {	
	fire.nextFrame((int) (_graphic.getCurrentTicks() * SPRITE_SPEED));
	hero.nextFrame((int)(_graphic.getCurrentTicks() * SPRITE_SPEED));
	hero2.nextFrame((int)(_graphic.getCurrentTicks() * SPRITE_SPEED));
	hero3.nextFrame((int)(_graphic.getCurrentTicks() * SPRITE_SPEED));
	hero4.nextFrame((int)(_graphic.getCurrentTicks() * SPRITE_SPEED));
}

/**
* Draw the game objects on the screen
*/
void Game::renderGame() {			
		//Clear the screen
	_graphic.clearWindow();
		//Draw basic elements
	_graphic.drawFilledRectangle(RED, 20, 50, 660, 150);
	_graphic.drawFilledRectangle(BLUE, 20, 200, 660, 150);
	_graphic.drawFilledRectangle(GREEN, 20, 350, 660, 150);
	_graphic.drawFilledRectangle(WHITE, 20, 500, 660, 150);

		//Draw some sprites
	drawSprite(hero);
	drawSprite(hero2);
	drawSprite(hero3);
	drawSprite(hero4);
		//Refresh screen
	_graphic.refreshWindow();	
}

/*
* Draw the sprite on the screen
* @param sprite is the sprite to be displayed
*/
void Game::drawSprite(Sprite & sprite) {
	_graphic.drawTexture(sprite.getSpriteId(), SPRITE_DEFAULT_WIDTH*sprite.getCurrentFrame(), 0, SPRITE_DEFAULT_WIDTH, SPRITE_DEFAULT_HEIGHT
											 , sprite.getXAtWorld(), sprite.getYAtWorld(), SPRITE_DEFAULT_WIDTH, SPRITE_DEFAULT_HEIGHT);
}


