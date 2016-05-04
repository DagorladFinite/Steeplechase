#include "Sprite.h"

/*
* Default constructor
*/
Sprite::Sprite() :_xAtWorld(0), _yAtWorld(0),_width(SPRITE_DEFAULT_WIDTH), _height(SPRITE_DEFAULT_HEIGHT), _textureID(-1), _currentFrame(0), _currentVerticalFrame(0), _maxFrames(1) { }

/*
* Destructor
*/
Sprite::~Sprite() {}

/*
* Initialize the character values
* @param newX is the new X position at World
* @param newy is the new Y position at World
* @param textureId is the texture that represents the character
* @param currentFrame is the initial frame that will be shown
* @param maxFrames is the maximal number of frames. This value is greater than 1 means that the character is animated
*/
void Sprite::setInitialValues(int newXPosition, int newYPosition, int width, int height, int textureId, int currentFrame,int currentVerticalFrame, int maxFrames) {
	_xAtWorld = newXPosition;
	_yAtWorld = newYPosition;
	_width = width;
	_height = height;
	_textureID = textureId;
	_currentFrame = currentFrame;
	_currentVerticalFrame = currentVerticalFrame;
	_maxFrames = maxFrames;
}

/*
* Set a new position in the world
* @param newX is the new X position at World
* @param newy is the new Y position at World
*/
void Sprite::setPositionAtWorld(int newX, int newY) {
	_xAtWorld = newX;
	_yAtWorld = newY;
}

/*
* Get the sprite id used by the game element
* @return an int value with the sprite id
*/
int Sprite::getSpriteId() {
	return _textureID;
}

/*
* Get the x position of the game element
* @return an int value with the x position
*/
int Sprite::getXAtWorld() {
	return _xAtWorld;
}

/*
* Get the y position of the game element
* @return an int value with the y position
*/
int Sprite::getYAtWorld() {
	return _yAtWorld;
}

/*
* Get the sizes of the sprite
*/

int Sprite::getWidth() {
	return _width;
}
int Sprite::getHeight() {
	return _height;
}



/*
* Get the number of frames of the sprite
* @return an int value with the number of frames of the sprite. If it is equal to 1, there is no animation
*/
int Sprite::getMaxFrames() {
	return _maxFrames;
}

/*
* Get the current frame of the sprite
* @return an int value with the current frame
*/
int Sprite::getCurrentFrame() {
	return _currentFrame;
}

/* Set the current frame
* @param newCurrentFrame is the new current frame
*/
void Sprite::setCurrentFrame(int newCurrentFrame) {
	_currentFrame = newCurrentFrame;
}

int Sprite::getCurrentVerticalFrame() {
	return _currentVerticalFrame;
}

void Sprite::setCurrentVerticalFrame(int newCurrentVerticalFrame) {
	_currentVerticalFrame = newCurrentVerticalFrame;
}




/*
* Change the current frame for the next in the list
*/
void Sprite::nextFrame(int nextValue) {
	_currentFrame = nextValue % _maxFrames;
}

void Sprite::move(int x, int y){
	//std::cout << _xAtWorld <<" -- " << _yAtWorld << std::endl;
	setPositionAtWorld(_xAtWorld + x, _yAtWorld + y);
	//std::cout << _xAtWorld << " -- " << _yAtWorld << std::endl;

}
