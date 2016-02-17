#pragma once
#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
#include <Windows.h>
#include <string>

class SocketTools
{
public:
	static int CargarLibreria();
	static int DescargarLibreria();
	static void MostrarError(std::string mensaje);
};

