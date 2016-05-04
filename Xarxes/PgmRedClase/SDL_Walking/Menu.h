#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <string>
#include "GameConstants.h"
#include "Button.h"

class Menu{
private:
	Button _options;
	Button _resume;
	Button _exit;
	Sprite _menu;

public:
	//Constuctors
	Menu();
	~Menu();

	//Getters
	inline Sprite getOptionsSprite() { return _options.getButtonSprite(); }
	inline Sprite getResumaSprite() { return _resume.getButtonSprite(); }
	inline Sprite getExitSprite() { return _exit.getButtonSprite(); }
	inline int getMenuSpriteID() { return _menu.getSpriteId(); }
	//Setters


	//Funcitons
	GameState Menu::checkIfButtonIsPressed(bool _mouseIsPressed, glm::ivec2 mousePositon);
	void Menu::checkIfMouseisOverButton(glm::ivec2 mousePositon);
};

