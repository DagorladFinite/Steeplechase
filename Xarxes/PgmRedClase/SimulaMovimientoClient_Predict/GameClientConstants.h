#pragma once
#include <GameConstants.h>

//Game general information
#define GAME_SPEED 0.1f
#define GAME_TEXTURES 2
#define SCREEN_WIDTH 700
#define SCREEN_HEIGHT 300
#define SIZE_SQUARE 40

//Color information
#define GAME_BASIC_COLORS 5
#define RED 0
#define GREEN 1
#define BLUE 2
#define BLACK 3
#define WHITE 4


//Game has four possible states: INIT (Preparing environment), PLAY (Playing), EXIT (Exit from the game) or MENU (Game menu)
enum class GameState{ INIT, PLAY, EXIT, MENU };
enum class NetworkState { UNINITIALIZED, SAYINGHELLO, WELCOMED };

#define FREQUENCY_SAYING_HELLO 200
#define FREQUENCY_SENDING_INPUTS 100