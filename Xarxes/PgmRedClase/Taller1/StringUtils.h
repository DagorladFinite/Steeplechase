#pragma once
#include <memory>
#include <string>
#include <iostream>

class StringUtils
{
public:
static void ConvertTo4Bytes(std::string direccion, uint8_t aBytes[4])
{
	int posPunto1 = direccion.find_first_of('.');
	std::string b1 = direccion.substr(0, posPunto1);
	int posPunto2 = direccion.find('.', posPunto1 + 1);
	std::string b2 = direccion.substr(posPunto1+1, posPunto2 -(posPunto1 + 1));
	int posPunto3 = direccion.find('.', posPunto2 + 1);
	std::string b3 = direccion.substr(posPunto2 + 1, posPunto3 - (posPunto2 + 1));
	int posPunto4 = direccion.find('.', posPunto3 + 1);
	std::string b4 = direccion.substr(posPunto3 + 1, posPunto4 - (posPunto3 + 1));

	aBytes[0] = atoi(b1.c_str());
	aBytes[1] = atoi(b2.c_str());
	aBytes[2] = atoi(b3.c_str());
	aBytes[3] = atoi(b4.c_str());
	
	
}

static int PideDatosTeclado(char* aDatos)
{
	std::string strDatos;
	std::getline(std::cin, strDatos);
	int longitud = strDatos.length();

	for (int i = 0; i < longitud; i++)
	{
		aDatos[i] = strDatos[i];
	}
	aDatos[longitud] = '\0';
	return longitud;
}
};