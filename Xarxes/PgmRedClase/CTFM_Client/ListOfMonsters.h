#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <string>
#include "Sprite.h"
#include "GameConstantsClient.h"
#include <vector>

class ListOfMonsters
{
	std::vector<Sprite> monsters;
public:
	ListOfMonsters();
	~ListOfMonsters();
	Sprite& operator[](int p_index);
	int size();
	void Deserialize(std::string _strMonsters);
	
	void nextAnimationFrame(int curTicks);
	
};

