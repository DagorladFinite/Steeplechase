#pragma once

//Game general information
#define SCREEN_WIDTH 700
#define SCREEN_HEIGHT 700
#define GAME_SPEED 0.1f
#define GAME_TEXTURES 21
#define MAX_MONSTERS 10
#define MONSTER_REFRESH_FREQUENCY 500
#define MAP_COLUMS 12	
#define MAP_ROWS 12		
#define PLAYER_SPEED 3

//Sprite information
#define SPRITE_SPEED 0.01f
#define SPRITE_DEFAULT_WIDTH 64
#define SPRITE_DEFAULT_HEIGHT 64
#define MENU_BUTTON_DEFAULT_WIDTH 255
#define MENU_BUTTON_DEFAULT_HEIGHT 50
#define SPRITE_HERO 0
#define SPRITE_FIRE 1
#define SPRITE_MENU 18
#define SPRITE_START_MENU 19
#define SPRITE_BUTTON_OPTIONS 14
#define SPRITE_BUTTON_RESUME 15
#define SPRITE_BUTTON_EXIT 16
#define SPRITE_BUTTON_NEWGAME 17
#define SPRITE_LIVES 20

//Terrain Sprites Info
#define SPRITE_TERRAIN_GRASS_ALL 2
#define SPRITE_TERRAIN_ROAD_HOROZONTAL 3
#define SPRITE_TERRAIN_ROAD_VERTICAL 4
#define SPRITE_TERRAIN_DIRT 5
#define SPRITE_TERRAIN_DIRT_B 6
#define SPRITE_TERRAIN_DIRT_T 7
#define SPRITE_TERRAIN_DIRT_L 8
#define SPRITE_TERRAIN_DIRT_R 9
#define SPRITE_TERRAIN_DIRT_OBR 10
#define SPRITE_TERRAIN_DIRT_OBL 11
#define SPRITE_TERRAIN_DIRT_OTR 12
#define SPRITE_TERRAIN_DIRT_OTL 13


//Color information
#define GAME_BASIC_COLORS 5
#define RED 0
#define GREEN 1
#define BLUE 2
#define BLACK 3
#define WHITE 4


//Game has four possible states: INIT (Preparing environment), PLAY (Playing), EXIT (Exit from the game) or MENU (Game menu)
enum class GameState{ INIT, START, PLAY, EXIT, MENU };

