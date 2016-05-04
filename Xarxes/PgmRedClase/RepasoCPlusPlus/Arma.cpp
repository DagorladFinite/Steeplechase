#include "Arma.h"



Arma::Arma()
{
	std::cout << "Arma::Constructor por defecto"<<std::endl;
}

Arma::Arma(char nombre[20], int peso, int puntos)
{
	std::cout << "Arma::Constructor por parámetros" << std::endl;
	strcpy_s(this->nombre, nombre);
	this->peso = peso;
	this->puntos = puntos;
}

Arma::Arma(Arma & arma):Arma(arma.nombre, arma.peso, arma.puntos)
{
	std::cout << "Arma::Constructor de copia" << std::endl;
}


Arma::~Arma()
{
	std::cout << "Arma::Destructor" << std::endl;
}

std::ostream& operator<<(std::ostream& os, Arma & arma)
{
	os << "Nombre Arma: " << arma.nombre << "\n" << "Peso: " << arma.peso << "\nPuntos: " << arma.puntos;
	return os;
}

std::istream& operator>>(std::istream& is, Arma & arma)
{
	std::cout << "Nombre: ";
	is >> arma.nombre;
	std::cout << "Peso: ";
	is >> arma.peso;
	std::cout << "Puntos: ";
	is >> arma.puntos;

	return is;
}
