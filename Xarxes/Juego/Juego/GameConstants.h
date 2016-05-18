#pragma once

//Game general information
#define GAME_SPEED 0.1f
#define GAME_TEXTURES 3


//Sprite information
#define SPRITE_SPEED 0.01f
#define SPRITE_DEFAULT_WIDTH 64
#define SPRITE_DEFAULT_HEIGHT 64
#define SPRITE_HERO 0
#define SPRITE_FIRE 1
#define LOAD 2
#define TRACK 3

//Color information
#define GAME_BASIC_COLORS 5
#define RED 1
#define GREEN 2
#define BLUE 3
#define BLACK 4
#define WHITE 0


//Game has four possible states: INIT (Preparing environment), PLAY (Playing), EXIT (Exit from the game) or MENU (Game menu)
enum class GameState{ INIT, PLAY, EXIT, MENU };

