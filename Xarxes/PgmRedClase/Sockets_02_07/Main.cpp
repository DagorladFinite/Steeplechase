#pragma once
#include <TCPSocket.h>
#include <SocketTools.h>
#include <string>



int PideDatosTeclado(char* aDatos)
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

void Servidor(std::string direccionBind)
{
	TCPSocket tcpSocket;
	SocketAddress sa;
	sa.SetAddress(direccionBind);
	tcpSocket.Bind(sa);
	tcpSocket.Listen(10);


	SocketAddress from;
	std::shared_ptr<TCPSocket> socketRecepcion = tcpSocket.Accept(from);

	while (true)
	{
		char data[1300];
		int bytesReceived = socketRecepcion->Receive(data, 1300);
		if (bytesReceived > 0)
		{
			if (bytesReceived < 1300)
			{
				data[bytesReceived] = '\0';
			}
			std::cout << "> " << data << std::endl;
			if (strcmp(data, "exit") == 0)
			{
				break;
			}
		}
	}
}

void Cliente(std::string direccionConexion)
{
	TCPSocket tcpSocket;
	SocketAddress sa;
	sa.SetAddress(direccionConexion);
	int err = tcpSocket.Connect(sa);
	if (err != -1)
	{
		while (true)
		{
			char datos[1300];
			PideDatosTeclado(datos);
			tcpSocket.Send(datos);
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
	SocketTools::DescargarLibreria();
	
}