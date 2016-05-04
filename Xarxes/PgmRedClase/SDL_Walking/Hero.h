#pragma once

#include "Sprite.h"
#include "GameConstants.h"

class Hero{
private:
	Sprite _hero;
	Sprite _lives;
	bool _isMoving;

public:
	//Constructors
	Hero();
	~Hero();

	//Setters
	void setMovementUp();
	void setMovementDown();
	void setMovementLeft();
	void setMovementRight();
	inline void setMoving(bool move) { _isMoving = move; }
	//Getters
	inline int getXAtWorld() { return _hero.getXAtWorld(); }
	inline int getYAtWorld() { return _hero.getYAtWorld(); }
	inline Sprite getHeroSprite() { return _hero; }
	inline Sprite getLivesSprite() { return _lives; }
	inline bool isMoving() { return _isMoving; }

	//Functions
	void initialize();
	void nextAnimationFrame(int curTicks);
	inline void move(int x, int y) { _hero.move(x, y); }

};

