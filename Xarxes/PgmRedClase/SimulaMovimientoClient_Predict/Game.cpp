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
	_graphic.setWindowBackgroundColor(0, 0, 0, 255);
		//Set the font style
	_graphic.setFontStyle(TTF_STYLE_NORMAL);
		//Initialize the game elements
}


/*
* Game execution: Gets input events, processes game logic and draws sprites on the screen
*/
void Game::gameLoop() {	
	_gameState = GameState::PLAY;
	while (_gameState != GameState::EXIT) {		
		if (_network.GetNetworkState() == NetworkState::SAYINGHELLO)
		{
			_network.SayHello();
		}

		int positionSquare = aSquares[_network.GetIdSquare()].GetPosition();
		_network.SendMove(positionSquare,_inputState, _inputStateList);
		
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
	int numBytes = _network.Receive(strReceived);
	
	if (numBytes > 0)
	{
		//std::cout << "Recibo: " << strReceived << std::endl;
		int index_ = strReceived.find_first_of('_');
		std::string cabecera = strReceived.substr(0, index_);
		std::string contenido = strReceived.substr(index_ + 1, strReceived.size() - index_);
		
		if (cabecera == HEADER_WELCOME)
		{
			_network.SetIdSquare(atoi(contenido.c_str()));
			//std::cout << "Estado a WELCOMED" << std::endl;
			_network.SetNetworkState(NetworkState::WELCOMED);
		}
		else if (cabecera == HEADER_FULL)
		{

		}
		else if (cabecera == HEADER_POSITION)
		{
			std::cout << "Recibo " << strReceived << std::endl;
			int index_ = contenido.find_first_of('_');
			std::string strIdAck = contenido.substr(0, index_);
			std::string contentPosition = contenido.substr(index_ + 1, contenido.size() - index_);

			int index2ptos = contentPosition.find_first_of(':');
			std::string strIdSquare = contentPosition.substr(0, index2ptos);
			std::string strPosition = contentPosition.substr(index2ptos + 1, contentPosition.size() - index2ptos);

			int idSquare = atoi(strIdSquare.c_str());
			int position = atoi(strPosition.c_str());

			if (idSquare == _network.GetIdSquare())
			{
				//Sacamos el InputState de la lista
				int idAck = atoi(strIdAck.c_str());
				bool okPosition = _inputStateList.Acknowledge(idAck, position);

				//aSquares[idSquare].SetPosition(position);
				if (!okPosition)
				{
					//Ahora sólo corrijo si la predicción esta mal.
					aSquares[idSquare].SetPosition(position);
				}
			}
			else
			{
				aSquares[idSquare].SetPosition(position);
			}

			std::cout << "Confirman: " << position << std::endl;
			

		}
		else if (cabecera == HEADER_EXIT)
		{
			_gameState = GameState::EXIT;
		}
	}
}

/**
* Executes the actions sent by the user by means of the keyboard and mouse
* Reserved keys:
- up | left | right | down moves the player object
- m opens the menu
*/
void Game::executePlayerCommands() {

	if (_graphic.isKeyDown(SDLK_RIGHT)){
		//int position = aSquares[_network.GetIdSquare()].GetPosition();
		//2-std::cout << "Derecha "/* << std::to_string(position) */<< std::endl;
		//std::string msg = "TRYPOSITION_" + std::to_string(position + 1);
		//2-std::string msg = "TRYPOSITION_" + std::to_string( 1);
		//2-network.Send(msg);
		//3-
		_inputState.AddRight();
		aSquares[_network.GetIdSquare()].AddRight();
	}
	if (_graphic.isKeyDown(SDLK_LEFT)) {
		//int position = aSquares[_network.GetIdSquare()].GetPosition();
		//2-std::cout << "Izquierda "/* << std::to_string(position) */<< std::endl;
		//std::string msg = "TRYPOSITION_" + std::to_string(position - 1);
		//2-std::string msg = "TRYPOSITION_" + std::to_string(-1);
		//2-_network.Send(msg);
		//3-
		_inputState.AddLeft();
		aSquares[_network.GetIdSquare()].AddLeft();
	}
	if (_graphic.isKeyPressed(SDLK_ESCAPE)) {
		_gameState = GameState::EXIT;
		_network.Send("EXIT");
	}
}

/*
* Execute the game physics
*/
void Game::doPhysics() {
	

	
}

/**
* Render the game on the screen
*/
void Game::renderGame() {
		//Clear the screen
	_graphic.clearWindow();

		//Draw the screen's content based on the game state
	if (_gameState == GameState::MENU) {
		drawMenu();
	}
	else {
		drawGame();
	}
		//Refresh screen
	_graphic.refreshWindow();
}

/*
* Draw the game menu
*/
void Game::drawMenu() {

}

/*
* Draw the game, winner or loser screen
*/
void Game::drawGame() {

	_graphic.drawFilledRectangle(BLUE, 0, 0, 20, 300);
	_graphic.drawFilledRectangle(BLUE, 680, 0, 20, 300);
	
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		int position = aSquares[i].GetPosition();
		_graphic.drawFilledRectangle(i, position, 40 + 180*i, SIZE_SQUARE, SIZE_SQUARE);
	}
}

/*
* Draw the sprite on the screen
* @param sprite is the sprite to be displayed
*/
void Game::drawSprite(Sprite & sprite) {
	//_graphic.drawTexture(sprite.getSpriteId(), MONSTER_DEFAULT_WIDTH*sprite.getCurrentFrame(), 0, MONSTER_DEFAULT_WIDTH, MONSTER_DEFAULT_HEIGHT
	//	, sprite.getXAtWorld(), sprite.getYAtWorld(), MONSTER_DEFAULT_WIDTH, MONSTER_DEFAULT_HEIGHT);
}