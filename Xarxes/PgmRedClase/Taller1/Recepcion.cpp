#include "Recepcion.h"
#include <SocketTools.h>

Recepcion::Recepcion(std::string miDireccion, Buffer* _buffer):Comunicacion(miDireccion, _buffer)
{
	int err = udpSocket->Bind(sa);
}

void Recepcion::operator()()
{
	SocketAddress RemoteAddress;

	while (true)
	{
		char cadena[1300];
		int longDatos = udpSocket->ReceiveFrom(cadena, 1300, RemoteAddress);

		if (longDatos > 0)
		{
			cadena[longDatos] = '\0';
			buffer->Encolar(cadena);
			int cmp = strcmp("exit", cadena);
			if (cmp == 0)
			{
				break;
			}
			buffer->Mostrar();
		}
	}
}


Recepcion::~Recepcion()
{
}


