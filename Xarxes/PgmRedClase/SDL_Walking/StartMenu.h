#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <string>
#include "GameConstants.h"
#include "Button.h"

class StartMenu{
private:
	Button _newGame;
	Button _exit;
	Sprite _menu;

public:
	//Constructors
	StartMenu();
	~StartMenu();

	//Getters
	inline Sprite getNewGameSprite() { return _newGame.getButtonSprite(); }
	inline Sprite getExitSprite() { return _exit.getButtonSprite(); }
	inline int getMenuSpriteID() { return _menu.getSpriteId(); }

	//Functions
	GameState StartMenu::checkIfButtonIsPressed(bool _mouseIsPressed, glm::ivec2 mousePositon);
	void StartMenu::checkIfMouseisOverButton(glm::ivec2 mousePosition);
};

