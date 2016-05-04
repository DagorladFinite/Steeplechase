#include "Game.h"

/**
* Constructor
* Tip: You can use an initialization list to set its attributes
* @param windowTitle is the window title
* @param screenWidth is the window width
* @param screenHeight is the window height
*/
Game::Game(std::string windowTitle, int screenWidth, int screenHeight, std::string serverAddress, std::string clientAddress, std::string nick) :
	_windowTitle(windowTitle),
	_screenWidth(screenWidth),
	_screenHeight(screenHeight),
	_gameState(GameState::INIT),
	_network(serverAddress, clientAddress, nick)
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
	srand((unsigned int)time(NULL));
		//Create a window
	_graphic.createWindow(_windowTitle, _screenWidth, _screenHeight, false);	
	_graphic.setWindowBackgroundColor(255, 255, 255, 255);
		//Load the sprites associated to the different game elements
	_graphic.loadTexture(SPRITE_FIRE, "../sharedResources/images/characters/fireSprite.png");
		//Set the font style
	_graphic.setFontStyle(TTF_STYLE_NORMAL);
		//Initialize the game elements
			//The different monsters
}


/*
* Game execution: Gets input events, processes game logic and draws sprites on the screen
*/
void Game::gameLoop() {	
	while (_gameState == GameState::INIT)
	{
		_network.SayHello();
		Receiving();
		renderGame();
	}
	while (_gameState == GameState::PLAY) {		
		Receiving();
		//Update the game physics
		doPhysics();
		//Detect keyboard and/or mouse events
		_graphic.detectInputEvents();
		//Execute the player commands 
		executePlayerCommands();
		//Render game
		renderGame();			
	}
}

void Game::Receiving()
{
	std::string strReceived;
	int bytesReceived = _network.Receive(strReceived);
	if (bytesReceived <= 0)
	{
		return;
	}
	int index_ = strReceived.find_first_of('_');
	std::string cabecera = strReceived.substr(0, index_);
	if (cabecera == std::string(HEADER_WELCOME) && _gameState == GameState::INIT)
	{
		//TODO: Cambio el estado _network a NetworkClientState::NCS_Welcomed
		
	}
	else if (cabecera == std::string(HEADER_BEGIN) && _gameState == GameState::INIT)
	{
		//Cuando me llega el BEGIN, lanzo el clock. En este caso se controla desde cliente porque no hacemos "records"
		std::cout << "Inicio el clock" << std::endl;
		_initTimePlaying = clock();
	}
	else if (cabecera == std::string(HEADER_END))
	{
		//Cuando llega end, acabo el juego. Se indica con GameState:EXIT
		_gameState = GameState::EXIT;
	}
	else if (cabecera == std::string(HEADER_MONSTERS))
	{
		_gameState = GameState::PLAY;
		//La función Deserialize coge el mensaje, lo descompone y lo carga en la lista de mosntruos de _monsters.
		_monsters.Deserialize(strReceived);
	}
}

/**
* Executes the actions sent by the user by means of the keyboard and mouse
* Reserved keys:
- up | left | right | down moves the player object
- m opens the menu
*/
void Game::executePlayerCommands() {

	if (_graphic.isKeyPressed(SDL_BUTTON_LEFT) && _monsters.size() > 0){
		glm::ivec2 mouseCoords = _graphic.getMouseCoords();
		
		//TODO: Crear el mensaje POSITION y enviarlo a servidor
	}

	if (_graphic.isKeyPressed(SDLK_ESCAPE)) {
		//Si quisiéramos avisar de que el jugador cierra el juego, lo haríamos aquí.
		_gameState = GameState::EXIT;
	}
}

/*
* Execute the game physics
*/
void Game::doPhysics() {
	

	if (_monsters.size()!=0)	{
			//Update the animation of monsters
		_monsters.nextAnimationFrame(_graphic.getCurrentTicks());
		
	}	
}

/**
* Render the game on the screen
*/
void Game::renderGame() {
	//Clear the screen
	_graphic.clearWindow();

		
	if (_gameState == GameState::INIT) 
	{
		//Cuando aun no he empezado a jugar
		//Mensajes de conectando, esperando ,etc.
		drawInitInfo();
	}
	else if (_gameState == GameState::PLAY) 
	{
		//Estoy jugando --> Dibuja los monstruos
		drawGame();
	}
		//Refresh screen
	_graphic.refreshWindow();
}

/*
* Draw the game menu
*/
void Game::drawInitInfo() 
{
	NetworkClientState state = _network.GetState();

	switch (state)
	{
	case NetworkClientState::NCS_Uninitialized:
		//TODO: Mostrar un mensaje de "Iniciando..."

		break;
	case NetworkClientState::NCS_SayingHello:
		//TODO: Mostrar un mensaje de "Conectando con servidor..."
		
		break;
	case NetworkClientState::NCS_Welcomed:
		//TODO: Mostrar un mensaje de "Esperando jugadores..."
		
		break;
	default:
		break;
	}
	
}

/*
* Draw the game menu
*/
void Game::drawMenu() {

}

/*
* Draw the game, winner or loser screen
*/
void Game::drawGame()	{
		
	if (_network.GetState() == NetworkClientState::NCS_Welcomed && _gameState == GameState::PLAY) {
		//Draw the list of monsters
		for (int i = 0; i < _monsters.size(); i++) {
			drawSprite(_monsters[i]);
		}
		//Draw the current time
		_graphic.drawText("Current time: " + std::to_string((clock() - _initTimePlaying) / 1000) + " seconds", BLACK, WHITE, 0, 0);
	}
}

/*
* Draw the sprite on the screen
* @param sprite is the sprite to be displayed
*/
void Game::drawSprite(Sprite & sprite) {
	_graphic.drawTexture(sprite.getSpriteId(), MONSTER_DEFAULT_WIDTH*sprite.getCurrentFrame(), 0, MONSTER_DEFAULT_WIDTH, MONSTER_DEFAULT_HEIGHT
		, sprite.getXAtWorld(), sprite.getYAtWorld(), MONSTER_DEFAULT_WIDTH, MONSTER_DEFAULT_HEIGHT);
}