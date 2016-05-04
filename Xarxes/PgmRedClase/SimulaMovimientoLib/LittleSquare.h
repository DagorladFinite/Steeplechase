#pragma once
#include "GameConstants.h"
class LittleSquare
{
private:
	int position;

public:
	
	LittleSquare(int _position);
	LittleSquare(const LittleSquare& littleSquare);
	int GetPosition();
	void SetPosition(int _position);
	~LittleSquare();
};
