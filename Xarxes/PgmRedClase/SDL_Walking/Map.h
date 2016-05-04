#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <string>
#include "Sprite.h"
#include "SDLInterface.h"
#include "GameConstants.h"
#include "Cell.h"
#include <iostream>


class Map {
private:
	Cell  * * _terrain;
	int _colums, _rows;
	int _mapNum;
	int _xDisp, _yDisp;
	SDLInterface _graphic;
	void drawSprite(int idTexture, int x, int y);

public:
	//Constructors
	Map();
	Map(int mapNum);
	Map(int x, int y);
	//Destructor
	~Map();

	//Getters
	inline int GetXDisp() { return _colums; }
	inline int GetYDisp() { return _rows; }
	//Setters
	void setSDLInterface(SDLInterface & _graphic);
	void setDownMap(int ** map);
	//Functions
	void init();
	void move(int x, int y);
	void renderMap();
};
