#pragma once
#include <GameConstants.h>

enum class NetworkClientState
{
	NCS_Uninitialized,
	NCS_SayingHello,
	NCS_Welcomed
};

#define FREQUENCY_SAYING_HELLO 200
//Game has four possible states: INIT (Preparing environment), PLAY (Playing), EXIT (Exit from the game) or MENU (Game menu)
enum class GameState { INIT, PLAY, EXIT, MENU };

//Sprite information
#define SPRITE_SPEED 0.01f
#define SPRITE_HERO 0
#define SPRITE_FIRE 1
#define GAME_TEXTURES 2


//Color information
#define GAME_BASIC_COLORS 5
#define RED 0
#define GREEN 1
#define BLUE 2
#define BLACK 3
#define WHITE 4


