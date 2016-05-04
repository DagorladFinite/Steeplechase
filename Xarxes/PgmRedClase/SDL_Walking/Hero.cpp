#include "Hero.h"



Hero::Hero()
{
	_hero.setInitialValues(100, 100, 64, 64, SPRITE_HERO, 0, 0, 4);
	_lives.setInitialValues(15, 15, 156, 50, SPRITE_LIVES, 0, 0, 7);
	_isMoving = false;
}


Hero::~Hero()
{
}

void Hero::initialize() {
	_hero.setInitialValues(100, 100, 64, 64, SPRITE_HERO, 0, 0, 4);
	_lives.setInitialValues(15, 15, 156, 50, SPRITE_LIVES, 0, 0, 7);
	_isMoving = false;
}

void Hero::setMovementUp() {
	_hero.setCurrentVerticalFrame(3);
}
void Hero::setMovementDown() {
	_hero.setCurrentVerticalFrame(0);
}
void Hero::setMovementLeft() {
	_hero.setCurrentVerticalFrame(1);
}
void Hero::setMovementRight() {
	_hero.setCurrentVerticalFrame(2);
}

void Hero::nextAnimationFrame(int curTicks) {
	if (_isMoving) {
		_hero.nextFrame((int)(curTicks * SPRITE_SPEED));
	}
	else {
		_hero.setCurrentFrame(0);
	}
}