#include "ListaHabilidades.h"



ListaHabilidades::ListaHabilidades()
{
}

ListaHabilidades::ListaHabilidades(ListaHabilidades & listaHabilidades)
{
	for (int i = 0; i < listaHabilidades.size(); i++) {
		push_back(listaHabilidades[i]);
	}
}

Habilidad ListaHabilidades::operator[](int pos)
{
	return at(pos);
}

void ListaHabilidades::Add(Habilidad a)
{
	push_back(a);
}

void ListaHabilidades::Add(std::string name, int mE)
{
	Habilidad a(name.c_str(), mE);
	Add(a);
}

void ListaHabilidades::Delete(Habilidad skill)
{
	//this->erase(std::find(this->begin(), this->end(), _skill));
	for (int i = 0; i < size(); i++)
	{
		if (at(i) == skill)
		{
			Delete(i);
			break;
		}
	}
}

void ListaHabilidades::Delete(int pos)
{
	this->erase(this->begin() + (pos));
}


ListaHabilidades::~ListaHabilidades()
{
}

std::ostream & operator<<(std::ostream & os, ListaHabilidades & lista)
{
	for (size_t i = 0; i < lista.size(); i++)
	{
		os << lista[i] << "\n";
	}
	return os;
}
