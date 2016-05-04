#include "Monster.h"



Monster::Monster()
{
}

Monster::Monster(int _x, int _y)
{
	x = _x;
	y = _y;
}

int Monster::GetX()
{
	return x;
}

int Monster::GetY()
{
	return y;
}

void Monster::SetX(int _x)
{
	x = _x;
}

void Monster::SetY(int _y)
{
	y = _y;
}


Monster::~Monster()
{
}
