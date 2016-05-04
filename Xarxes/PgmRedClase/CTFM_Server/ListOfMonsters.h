#pragma once
#include <string>
#include <GameConstants.h>
#include <vector>

class ListOfMonsters
{
	std::vector<std::pair<int, int>> aMonsters;
public:
	ListOfMonsters();
	~ListOfMonsters();

	int size();
	bool checkIfSomeMonsterDies(std::pair<int, int> _coord);
	void ReInitMonsters();
	void InitMonsters(int _length);
	std::string Serialize();
};

