#pragma once
#include <iostream>
#include <UDPSocket.h>
#include <SocketTools.h>
#include "StringTools.h"

void Servidor(std::string direccion)
{
	SocketAddress sa;
	sa.SetAddress(direccion);
	UDPSocket udpSocket;
	udpSocket.Bind(sa);
	udpSocket.NonBlocking(true);
	while (true)
	{
		char datos[1300];
		SocketAddress from;
		
		int bytesReceived = udpSocket.ReceiveFrom(datos, 1300, from);
		if (bytesReceived > 0)
		{
			datos[bytesReceived] = '\0';
			std::cout << "Recibo de "<<from<<": " << datos << std::endl;
			if (strcmp(datos, "exit") == 0)
			{
				break;
			}
		}
	}
}

void Cliente(std::string direccionDestino)
{
	UDPSocket udpSocket;
	SocketAddress saDestino;
	saDestino.SetAddress(direccionDestino);
	udpSocket.NonBlocking(true);
	while (true)
	{
		char datos[1300];
		int len = StringTools::PideDatosTeclado(datos);

		int bytesSend = udpSocket.SendTo(datos, len, saDestino);
		if (bytesSend > 0)
		{
			if (strcmp(datos, "exit") == 0)
			{
				break;
			}
		}
	}
}

int main(int argc, char** argv)
{
	SocketTools::CargarLibreria();
	
	std::string funcion = argv[1];
	std::string direccion = argv[2];
	
	if (funcion == "servidor")
	{
		Servidor(direccion);
	}
	else if (funcion == "cliente")
	{
		Cliente(direccion);
	}
	else
	{
		std::cout << "Función no válida" << std::endl;
	}
	

	SocketTools::DescargarLibreria();
}