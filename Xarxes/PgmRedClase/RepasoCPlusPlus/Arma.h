#pragma once
#include <iostream>

class Arma
{
private:
	char nombre[20];
	int peso, puntos;
public:
	Arma();
	Arma(char nombre[20], int peso, int puntos);
	Arma(Arma& arma);
	friend std::ostream& operator<<(std::ostream& os, Arma& arma);
	friend std::istream& operator>>(std::istream& os, Arma& arma);
	~Arma();
};

