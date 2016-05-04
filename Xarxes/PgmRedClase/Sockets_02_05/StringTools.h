#pragma once
#include <string>
#include <iostream>

class StringTools
{
public:
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