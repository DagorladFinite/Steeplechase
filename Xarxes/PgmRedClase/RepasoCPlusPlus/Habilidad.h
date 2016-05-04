#pragma once
#include <iostream>

class Habilidad
{
private:
	char nombre[20];
	int puntosExperienciaMinimos;
public:
	Habilidad();
	Habilidad(const char nombre[20], int puntosExperienciaMinimos);
	Habilidad(const Habilidad& habilidad);
	friend std::ostream& operator<<(std::ostream& os, Habilidad& habilidad);
	friend std::istream& operator>>(std::istream& is, Habilidad& habilidad);
	bool operator==(const Habilidad & h);
	~Habilidad();
};

