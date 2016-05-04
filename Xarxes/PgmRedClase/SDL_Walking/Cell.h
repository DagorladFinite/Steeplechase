#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <string>
#include "Sprite.h"
#include "SDLInterface.h"
#include "GameConstants.h"
#include <iostream>


class Cell {
private:
	int _up;	//Up Sprite ID
	int _down;	//Down Sprite ID
	bool _haveTwoLayers = false; //Have up Sprite

public:
	//Constructors
	Cell() : _haveTwoLayers(false) {};
	Cell(int down) : _down(down), _haveTwoLayers(false) {};
	Cell(int up, int down) : _down(down), _up(up), _haveTwoLayers(false) {}
	//Destructor
	~Cell() {};

	//Setters
	inline void setUpSprite(int up) { _up = up; _haveTwoLayers = true; }
	inline void setDownSprite(int down) { _down = down; }
	//Getters
	inline int getUpSprite() { return _up; }
	inline int getDownSprite() { return _down; }
	inline bool haveTwoLayers() { return _haveTwoLayers; }
};

