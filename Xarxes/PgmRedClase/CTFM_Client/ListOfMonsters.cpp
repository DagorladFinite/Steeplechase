#include "ListOfMonsters.h"


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
	return monsters.size();
}

/*
* Get a specified monster.This method is equivalent to getMonster();
* @param id identifies the monster
* @return a reference to the idTH monster, so, if user modifies it, the information of the data structure will be also modified
*/
Sprite& ListOfMonsters::operator[](int id) {
	if ((id < 0) && (id >= monsters.size())) throw std::exception("Invalid access to the data structure, this id doesn't exist");
	return monsters[id];
}

/**
 *	A partir de un string de mosntruos que nos ha llegado por internet, tenemos que volver a colocar
 *	los monstruos en nuestra pantalla.
 */
void ListOfMonsters::Deserialize(std::string _strMonsters)
{
	//Vaciamos la lista de monstruos. Las posiciones anteriores ya no las quiero para nada.
	monsters.clear();
	int index_ = _strMonsters.find_first_of('_');
	std::string header = _strMonsters.substr(0, index_);
	std::string content = _strMonsters.substr(index_ + 1, _strMonsters.size() - index_);
	//En content tendremos algo del estilo x:y#x:y#x:y
	// o numMonsters_x:y#x:y#x:y, si hemos querido pasar el número de monstruos que hay.

	//TODO: Hemos de "desmontar" este string para sacar las posiciones de cada uno de los monstruos y colocarlos
	
	//TODO: Para añadir el sprite de un monstruo a la lista, lo tenemos que hacer así
		/*Sprite s;
		s.setInitialValues(0, 0, SPRITE_FIRE, 0, 5);
		s.setPositionAtWorld(x, y);
		monsters.push_back(s);*/
	

	
}

/*
* Update the frame of all monsters
* @param curTicks is the current tick
*/
void ListOfMonsters::nextAnimationFrame(int curTicks) {
	for (int i = 0; i < monsters.size(); i++) {
		monsters[i].nextFrame((int)(curTicks * SPRITE_SPEED));
	}
}

