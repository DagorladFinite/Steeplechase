#include "Button.h"

/*
* Default constructor
*/
Button::Button(){}

/*
* Destructor
*/
Button::~Button(){}

void Button::setInitialButtonValues(int x, int y, int textureID) {
	_button.setInitialValues(x, y, MENU_BUTTON_DEFAULT_WIDTH, MENU_BUTTON_DEFAULT_HEIGHT, textureID, 0,0, 2);
}

void Button::setButtonPostition(int x, int y) {
	_button.setPositionAtWorld(x, y);
}

bool Button::checkIfButtonIsPressed(glm::ivec2 mousePositon){
	if (mousePositon.x >= _button.getXAtWorld() && mousePositon.x <= _button.getXAtWorld() + MENU_BUTTON_DEFAULT_WIDTH &&
		mousePositon.y >= _button.getYAtWorld() && mousePositon.y <= _button.getYAtWorld() + MENU_BUTTON_DEFAULT_HEIGHT) {
		return true;
	}
	else { return false; }
}
void Button::checkIfMouseisOverButton(glm::ivec2 mousePositon) {
	if (mousePositon.x >= _button.getXAtWorld() && mousePositon.x <= _button.getXAtWorld() + MENU_BUTTON_DEFAULT_WIDTH &&
		mousePositon.y >= _button.getYAtWorld() && mousePositon.y <= _button.getYAtWorld() + MENU_BUTTON_DEFAULT_HEIGHT) {
		_button.setCurrentFrame(1);
	}
	else {
		_button.setCurrentFrame(0);
	}
}