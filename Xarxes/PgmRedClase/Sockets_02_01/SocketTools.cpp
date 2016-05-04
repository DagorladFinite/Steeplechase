#include "SocketTools.h"
#include <iostream>

int SocketTools::CargarLibreria()
{
	WSAData data;
	int err = WSAStartup(MAKEWORD(2,2), &data);
	if (err == -1)
	{
		MostrarError("Error en SocketTools::DescargarLibrer�a");
	}
	return err;
}

int SocketTools::DescargarLibreria()
{
	int err = WSACleanup();
	if (err == -1)
	{
		MostrarError("Error en SocketTools::DescargarLibrer�a");
	}
	return err;
}

void SocketTools::MostrarError(std::string mensaje)
{
	std::cout << mensaje << ". ErrNo: " << WSAGetLastError() << std::endl;
}
