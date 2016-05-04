#pragma once
#include <vector>
#include "Habilidad.h"
#include <iostream>

class ListaHabilidades:private std::vector<Habilidad>
{
public:
	ListaHabilidades();
	ListaHabilidades(ListaHabilidades& listaHabilidades);
	friend std::ostream& operator<<(std::ostream& os, ListaHabilidades& lista);
	Habilidad operator[](int pos);
	void Add(Habilidad a);
	void Add(std::string name, int mE);
	void Delete(Habilidad skill);
	void Delete(int pos);
	~ListaHabilidades();
};

