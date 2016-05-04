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
	_gameState(GameState::INIT){
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
	_graphic.setWindowBackgroundColor(255, 255, 255, 255);
		//Load the sprites associated to the different game elements
	_graphic.loadTexture(SPRITE_HERO, "../sharedResources/images/characters/hero.png");
	_graphic.loadTexture(SPRITE_FIRE, "../sharedResources/images/characters/fireSprite.png");
		//Set the font style
	_graphic.setFontStyle(TTF_STYLE_NORMAL);
		//Initialize the game elements
	hero.setInitialValues(0, 0, SPRITE_HERO, 0, 4);
	fire.setInitialValues(100, 100, SPRITE_FIRE, 0, 5);
}


/*
* Game execution: Gets input events, processes game logic and draws sprites on the screen
*/
void Game::gameLoop() {	
	_gameState = GameState::PLAY;

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
}

/**
* Draw the game objects on the screen
*/
void Game::renderGame() {			
		//Clear the screen
	_graphic.clearWindow();
	
		//Draw some sprites
	drawSprite(hero);
	drawSprite(fire);

		//Draw basic elements
	_graphic.drawLine(RED, 500, 0, 500, 500);
	_graphic.drawFilledRectangle(RED, 300, 0, 150, 150);

	_graphic.drawText("Hello SDL", WHITE, RED, 300, 350);

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


