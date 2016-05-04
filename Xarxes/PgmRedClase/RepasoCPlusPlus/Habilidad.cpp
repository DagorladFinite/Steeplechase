#include "Habilidad.h"



Habilidad::Habilidad()
{
	//std::cout << "Habilidad::Constructor por defecto" << std::endl;
}

Habilidad::Habilidad(const char nombre[20], int puntosExperienciaMinimos)
{
	//std::cout << "Habilidad::Constructor por parámetros" << std::endl;
	strcpy_s(this->nombre, nombre);
	this->puntosExperienciaMinimos = puntosExperienciaMinimos;
}

Habilidad::Habilidad(const Habilidad & habilidad):Habilidad(habilidad.nombre, habilidad.puntosExperienciaMinimos)
{
	//std::cout << "Habilidad::Constructor de copia" << std::endl;
}


bool Habilidad::operator==(const Habilidad & h)
{
	if (strcmp(h.nombre, nombre) == 0) {
		return true;
	}
	return false;
}

Habilidad::~Habilidad()
{
	//std::cout << "Habilidad::Destructor" << std::endl;
	//system("pause");
}

std::ostream& operator<<(std::ostream& os, Habilidad & habilidad)
{
	os << "Nombre habilidad: " << habilidad.nombre << "\n" << 
		"Puntos de experiencia mínimos: " << habilidad.puntosExperienciaMinimos << "\n";
	return os;
}

std::istream& operator>>(std::istream& is, Habilidad & habilidad)
{
	std::cout << "Nombre: ";
	is >> habilidad.nombre;
	std::cout << "Puntos experiencia mínimos: ";
	is >> habilidad.puntosExperienciaMinimos;
	return is;
}
