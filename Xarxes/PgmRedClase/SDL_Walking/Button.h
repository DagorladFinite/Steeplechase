#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <string>
#include "Sprite.h"
#include "GameConstants.h"

class Button
{
	Sprite _button;

public:
	Button();
	~Button();
	void Button::setInitialButtonValues(int x, int y, int textureID);
	void Button::setButtonPostition(int screenWidth, int screenHeight);

	bool checkIfButtonIsPressed(glm::ivec2 mousePositon);
	void Button::checkIfMouseisOverButton(glm::ivec2 mousePositon);
	inline Sprite getButtonSprite() {return _button;}
};

