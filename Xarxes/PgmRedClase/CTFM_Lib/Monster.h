#pragma once
class Monster
{
private:
	int x, y;
public:
	Monster();
	Monster(int _x, int _y);
	int GetX();
	int GetY();
	void SetX(int _x);
	void SetY(int _y);
	~Monster();
};

