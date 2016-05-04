#include "ListOfMonsters.h"
#include <time.h>

/*
* Constructor
* @param n is the number of monsters to store
*/
ListOfMonsters::ListOfMonsters() {
	
}

/*
* Destructor
*/
ListOfMonsters::~ListOfMonsters(){
	
}

int ListOfMonsters::size()
{
	return aMonsters.size();
}

/**
 *  Si acertamos a uno o varios de los monstruos, se eliminan de la lista y se retorna true.
 *  False, en caso contrario.
 */
bool ListOfMonsters::checkIfSomeMonsterDies(std::pair<int, int> _coord)
{
	bool ret = false;
	for (int i = 0; i < size(); i++) {
		if (_coord.first >= aMonsters[i].first && _coord.first <= aMonsters[i].first + MONSTER_DEFAULT_WIDTH &&
			_coord.second >= aMonsters[i].second && _coord.second <= aMonsters[i].second + MONSTER_DEFAULT_HEIGHT)
		{
			aMonsters.erase(aMonsters.begin() + i);
			i--;
			ret = true;
		}
	}
	return ret;
}

void ListOfMonsters::ReInitMonsters()
{
	int sizeAnt = size();
	InitMonsters(sizeAnt);
}

/**
 *	Se genera una lista de _length monstruos con posiciones aleatorias según el tamaño de la ventana del jugador.
 */
void ListOfMonsters::InitMonsters(int _length)
{
	
	aMonsters.clear();
	for (size_t i = 0; i < _length; i++)
	{
		int x = rand() % (int)(SCREEN_WIDTH*0.9f);
		int y = rand() % (int)(SCREEN_HEIGHT*0.9f);
		aMonsters.push_back(std::pair<int, int>(x, y));
	}
}

/**
 *	Prepara el mensaje para ser enviado por la red.
 */
std::string ListOfMonsters::Serialize()
{
	int numMonsters = size();
	if (numMonsters == 0)
	{
		return "";
	}

	std::string ret = std::string(HEADER_MONSTERS)+"_";
	
	//TODO: Prepara el mensaje para enviar por internet.
	//TODO: Será algo del estilo MONSTERS_x:y#x:y#x:y
	//TODO: Si te resulta más cómo puede pasar el número de monstruos que hay: MONSTERS_num_x:y#x:y#x:y

	return ret;
}

