#include "Menu.h"



Menu::Menu()
{
	_options.setInitialButtonValues(225, 250, SPRITE_BUTTON_OPTIONS);
	_resume.setInitialButtonValues(225, 325, SPRITE_BUTTON_RESUME);
	_exit.setInitialButtonValues(225, 400, SPRITE_BUTTON_EXIT);
	_menu.setInitialValues(0, 0, 440, 390, SPRITE_MENU, 0,0, 1);
}


Menu::~Menu()
{
}

GameState Menu::checkIfButtonIsPressed(bool _mouseIsPressed,glm::ivec2 mousePosition) {
	if (_mouseIsPressed) {
		_mouseIsPressed = false;
		if (_resume.checkIfButtonIsPressed(mousePosition)) { return GameState::PLAY; }
		else if (_exit.checkIfButtonIsPressed(mousePosition)) { return GameState::START; }
		else { return GameState::MENU; }
	}
	else {
		return GameState::MENU;
	}
}
void Menu::checkIfMouseisOverButton(glm::ivec2 mousePosition) {
	_options.checkIfMouseisOverButton(mousePosition);
	_resume.checkIfMouseisOverButton(mousePosition);
	_exit.checkIfMouseisOverButton(mousePosition);
}