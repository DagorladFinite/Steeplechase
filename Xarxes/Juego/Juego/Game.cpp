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
	_graphic.loadTexture(LOAD, "../sharedResources/images/interface/load.png");
	_graphic.loadTexture(TRACK, "../sharedResources/images/interface/track.png");
	_graphic.loadTexture(HERO2, "../sharedResources/images/characters/her2o.png");
		//Set the font style
	_graphic.setFontStyle(TTF_STYLE_NORMAL);
		//Initialize the game elements
	int starty = 75;
	for (int i = 0; i < 4; i++)
	{
		if (i == network.playerNumber)
		{
			players[i].setInitialValues(10, starty, HERO2, 0, 4);
		}
		else {
			players[i].setInitialValues(10, starty, SPRITE_HERO, 0, 4);
			
		}
		starty += 150;
	}
	/*
	players[0].setInitialValues(10, 75, SPRITE_HERO, 0, 4);
	players[1].setInitialValues(10,225, SPRITE_HERO, 0, 4);
	players[2].setInitialValues(10, 375, SPRITE_HERO, 0, 4);
	players[3].setInitialValues(10, 525, SPRITE_HERO, 0, 4);
	*/

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

		if (network.Start()==true && s == false)
		{
			initplayers();
			s = true;
		}
			//Detect keyboard and/or mouse events
		_graphic.detectInputEvents();

			//Execute the player commands 
		executePlayerCommands();

		//Envíamos el input del jugador al servidor
		//Sólo lo enviaremos si ha pulsado el botón.

		if (moveSendCheck) {

			//Pérdida de paquetes. 
			//Tenemos un 1% de posibilidades de que "el paquete no llegue"
			int pickedChoice = (int)(rand() % 100) + 1;

			if (pickedChoice > 1) {
				network.sendMove();
			}
			else {
				std::cout << "¡Paquete perdido!" << std::endl;
			}


		}
		moveSendCheck = false;

			//Update the game physics
		doPhysics();

		network.serverCheaterBusterCheck;
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

	if (_graphic.isKeyPressed(SDLK_UP)) {
		if (network.status == 1) {
			if (players[network.playerNumber].getXAtWorld() < 640) {

				moveSendCheck = true;
				players[network.playerNumber].setPositionAtWorld(players[network.playerNumber].getXAtWorld(), 75 + (network.playerNumber*150)-25);
			}
		}
		
	}

	if (_graphic.isKeyDown(SDLK_LEFT)) {
		
	}
	if (_graphic.isKeyPressed(SDLK_DOWN)) {

		if (network.status == 1) {
			if (players[network.playerNumber].getXAtWorld() < 640) {

				moveSendCheck = true;
				players[network.playerNumber].setPositionAtWorld(players[network.playerNumber].getXAtWorld(), 75 + (network.playerNumber * 150) + 25);
			}
		}
		
	}

	if (_graphic.isKeyDown(SDLK_RIGHT)) {
		
	}

	if (_graphic.isKeyPressed(SDLK_SPACE)) {
		if(network.status ==1){
			if (players[network.playerNumber].getXAtWorld() < 640) {

				

				network.timesPressed++;
				moveSendCheck = true;
				network.playerPrevPositions[network.playerNumber] = network.playerPositions[network.playerNumber];
				players[network.playerNumber].setPositionAtWorld(players[network.playerNumber].getXAtWorld() + 3, players[network.playerNumber].getYAtWorld());
			}
		}
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

	//Actualizamos las posiciones de los jugadores con las posiciones que recibimos del servidor
	for (size_t i = 0; i < 4; i++)
	{
		players[i].setPositionAtWorld(network.playerPositions[i], players[i].getYAtWorld());
	}

	//Animación del pollo (Placeholder)
	players[0].nextFrame((int)(_graphic.getCurrentTicks() * SPRITE_SPEED));
	players[1].nextFrame((int)(_graphic.getCurrentTicks() * SPRITE_SPEED));
	players[2].nextFrame((int)(_graphic.getCurrentTicks() * SPRITE_SPEED));
	players[3].nextFrame((int)(_graphic.getCurrentTicks() * SPRITE_SPEED));
}

/**
* Draw the game objects on the screen
*/
void Game::renderGame() {			
		//Clear the screen
	_graphic.clearWindow();
	if (network.Start() == true)
	{
		_graphic.clearWindow();
		//Draw basic elements
		//_graphic.drawFilledRectangle(RED, 20, 50, 660, 150);
		_graphic.drawTexture(TRACK, 0, 0, 700, 700, 0, 0, 700, 700);
		//_graphic.drawTexture(TRACK, 10, 0, 660, 175, 10, 0, 660, 175);
		//_graphic.drawTexture(TRACK, 20, 350, 660, 175, 20, 350, 660, 175);
		//_graphic.drawTexture(TRACK, 20, 500, 660, 175, 20, 500, 660, 175);
		/*_graphic.drawFilledRectangle(BLUE, 20, 200, 660, 150);
		_graphic.drawFilledRectangle(GREEN, 20, 350, 660, 150);
		_graphic.drawFilledRectangle(WHITE, 20, 500, 660, 150);
		*/
		//Draw some sprites
		drawSprite(players[0]);
		drawSprite(players[1]);
		drawSprite(players[2]);
		drawSprite(players[3]);
	
	}
	else if (network.Start() == false) {
		_graphic.clearWindow();
		_graphic.drawTexture(LOAD, 0, 0, 700, 700, 0, 0, 700, 700);
		
	}
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

void Game::initplayers()
{
	int starty = 75;
	for (int i = 0; i < 4; i++)
	{
		if (i == network.playerNumber)
		{
			players[i].setInitialValues(10, starty, HERO2, 0, 4);
		}
		else {
			players[i].setInitialValues(10, starty, SPRITE_HERO, 0, 4);

		}
		starty += 150;
	}
}


