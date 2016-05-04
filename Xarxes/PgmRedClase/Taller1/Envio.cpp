#include "Envio.h"
#include <iostream>
#include "StringUtils.h"
#include <SocketTools.h>

Envio::Envio(std::string direccionDestino, Buffer* _buffer):Comunicacion(direccionDestino, _buffer)
{

}

void Envio::operator()()
{
	do {
		char datos[1300];

		Buffer::gotoxy(WRITE_POS_X, WRITE_POS_Y);
		std::cout << "> ";
		int longitud = StringUtils::PideDatosTeclado(datos);
		int sendBytes = udpSocket->SendTo(datos, longitud, sa);
		if (sendBytes > 0)
		{
			//std::cout << "Se han enviado " << sendBytes << std::endl;
			char datosEncolar[1300];
			strcpy_s(datosEncolar, datos);
			buffer->Encolar(datosEncolar);

			int cmp = strcmp(datos, "exit");
			if (cmp == 0)
			{
				break;
			}
			buffer->Mostrar();
		}
		else
		{
			std::cout << "Error al enviar " << sendBytes << std::endl;
		}

	} while (true);	
}



Envio::~Envio()
{
}
