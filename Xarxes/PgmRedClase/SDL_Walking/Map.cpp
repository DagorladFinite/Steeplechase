#include "Map.h"

//Constructors
Map::Map() {
	_colums = MAP_COLUMS;
	_rows = MAP_ROWS;
	_mapNum = 0;
	_xDisp = 0;
	_yDisp = 0;
}

Map::Map(int mapNum) {
	_colums = MAP_COLUMS;
	_rows = MAP_ROWS;
	_mapNum = mapNum;
	_xDisp = 0;
	_yDisp = 0;
}

Map::Map(int x, int y){
	_colums = x;
	_rows = y;
	_xDisp = 0;
	_yDisp = 0;
}

//Destructor
Map::~Map() {
}

//Setters
void Map::setSDLInterface(SDLInterface & graphic) {
	_graphic = graphic;
}

void Map::setDownMap(int ** map) {
	_terrain = 0;
	_terrain = new Cell*[_colums];

	for (int i = 0; i < _colums - 5; i++) {
		_terrain[i] = new Cell[_rows];
		for (int j = 0; j < _rows - 5; j++) {
			_terrain[i][j].setDownSprite(map[i][j]);
		}
	}
}

//---------- Functions ---------
void Map::init() {
	_terrain = 0;
	_terrain = new Cell*[_colums];

	for (int i = 0; i < _colums; i++) {
		_terrain[i] = new Cell[_rows];
		for (int j = 0; j < _rows; j++) {
			//Layer 2
			if (i == 0 || i == _colums - 1) _terrain[i][j].setDownSprite(SPRITE_TERRAIN_ROAD_HOROZONTAL);
			else if (j == 0 || j == _rows - 1) _terrain[i][j].setDownSprite(SPRITE_TERRAIN_ROAD_VERTICAL);
			else _terrain[i][j].setDownSprite(SPRITE_TERRAIN_GRASS_ALL);
			//Layer 1
			if (i == 4 && j == 3) _terrain[i][j].setUpSprite(SPRITE_TERRAIN_DIRT_OBR);
			else if (i == 4 && j == 7) _terrain[i][j].setUpSprite(SPRITE_TERRAIN_DIRT_OTR);
			else if (i == 7 && j == 3) _terrain[i][j].setUpSprite(SPRITE_TERRAIN_DIRT_OBL);
			else if (i == 7 && j == 7) _terrain[i][j].setUpSprite(SPRITE_TERRAIN_DIRT_OTL);
			else if (i > 4 && i < 8 && j == 3) _terrain[i][j].setUpSprite(SPRITE_TERRAIN_DIRT_B);
			else if (i > 4 && i < 8 && j == 7) _terrain[i][j].setUpSprite(SPRITE_TERRAIN_DIRT_T);
			else if (j > 3 && j < 7 && i == 4) _terrain[i][j].setUpSprite(SPRITE_TERRAIN_DIRT_R);
			else if (j > 3 && j < 7 && i == 7) _terrain[i][j].setUpSprite(SPRITE_TERRAIN_DIRT_L);
			else if (j > 3 && j < 7 && i > 4 && i < 7) _terrain[i][j].setUpSprite(SPRITE_TERRAIN_DIRT);
		}
	}
}

void Map::renderMap() {
	int x, y;

	for (int i = 0; i < _colums; i++) {
		for (int j = 0; j < _rows; j++) {	
			x = SPRITE_DEFAULT_WIDTH*i+ _xDisp;
			y = SPRITE_DEFAULT_WIDTH*j + _yDisp;

			if ((x >= -SPRITE_DEFAULT_WIDTH && x <= SCREEN_WIDTH + SPRITE_DEFAULT_WIDTH) &&
				(y >= -SPRITE_DEFAULT_HEIGHT && y <= SCREEN_HEIGHT + SPRITE_DEFAULT_HEIGHT)) {
				drawSprite(_terrain[i][j].getDownSprite(), x, y);

				if (_terrain[i][j].haveTwoLayers())
					drawSprite(_terrain[i][j].getUpSprite(), x, y);
			}
		}
	}
}

void Map::move(int x, int y){
	if(_xDisp+x<0 && _xDisp+x>(-SPRITE_DEFAULT_WIDTH*_colums)+SCREEN_WIDTH) _xDisp += x;
	if(_yDisp+y<0 && _yDisp+y>(-SPRITE_DEFAULT_HEIGHT*_rows)+SCREEN_HEIGHT)	_yDisp += y;
}
							   
void Map::drawSprite(int idTexture, int x, int y) {
	_graphic.drawTexture(idTexture, 1, 0, SPRITE_DEFAULT_WIDTH, 
		SPRITE_DEFAULT_HEIGHT, x, y, SPRITE_DEFAULT_WIDTH, SPRITE_DEFAULT_HEIGHT);
}