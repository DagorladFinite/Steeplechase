#pragma once
#include <iostream>
#include "GameConstants.h"

/* 
* The Character class represents a character of the game
*/

class Sprite {
	int _xAtWorld;
	int _yAtWorld;	
	int _textureID;
	int _width;
	int _height;
	int _currentFrame;
	int _currentVerticalFrame;
	int _maxFrames;

public:
	Sprite();
	~Sprite();

		//Getter and setter methods
	void setInitialValues(int x, int y, int width, int height, int textureID, int currentFrame, int currentVerticalFrame, int maxFrames);
	void setPositionAtWorld(int newXPosition, int newYPosition);
	int getXAtWorld();
	int getYAtWorld();
	int getWidth();
	int getHeight();
	int getSpriteId();
	int getMaxFrames();
	void setCurrentFrame(int newCurrentFrame);
	int getCurrentFrame();
	void setCurrentVerticalFrame(int newCurrentFrame);
	int getCurrentVerticalFrame();
	void nextFrame(int nextValue);
	void move(int x, int y);
	
	
};

