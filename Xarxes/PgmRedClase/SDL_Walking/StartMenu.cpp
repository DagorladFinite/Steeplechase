#include "StartMenu.h"



StartMenu::StartMenu()
{
	_newGame.setInitialButtonValues(225, 250, SPRITE_BUTTON_NEWGAME);
	_exit.setInitialButtonValues(225, 400, SPRITE_BUTTON_EXIT);
	_menu.setInitialValues(0, 0,700,700, SPRITE_START_MENU, 0, 0, 1);
}


StartMenu::~StartMenu()
{
}


GameState StartMenu::checkIfButtonIsPressed(bool _mouseIsPressed, glm::ivec2 mousePosition) {
	if (_mouseIsPressed) {
		_mouseIsPressed = false;
		if (_newGame.checkIfButtonIsPressed(mousePosition)) { return GameState::PLAY; }
		else if (_exit.checkIfButtonIsPressed(mousePosition)) { return GameState::EXIT; }
		else { return GameState::START; }
	}
	else {
		return GameState::START;
	}
}
void StartMenu::checkIfMouseisOverButton(glm::ivec2 mousePosition) {
	_newGame.checkIfMouseisOverButton(mousePosition);
	_exit.checkIfMouseisOverButton(mousePosition);
}