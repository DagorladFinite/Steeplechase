#include "Comunicacion.h"

Comunicacion::Comunicacion(std::string strDireccion, Buffer * _buffer)
{
	udpSocket = std::make_shared<UDPSocket>();
	sa.SetAddress(strDireccion);
	buffer = _buffer;
}

Comunicacion::~Comunicacion()
{
}
