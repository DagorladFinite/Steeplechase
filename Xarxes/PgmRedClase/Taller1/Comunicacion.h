#pragma once
#include "Buffer.h"
#include <UDPSocket.h>
#include <memory>

class Comunicacion
{
protected:
	std::shared_ptr<UDPSocket> udpSocket;
	SocketAddress sa;
	Buffer* buffer;
public:
	Comunicacion(std::string strDireccion, Buffer* _buffer);
	virtual void operator() ()=0;
	~Comunicacion();
};

