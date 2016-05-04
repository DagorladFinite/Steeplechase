#pragma once
#include "Comunicacion.h"


class Recepcion:public Comunicacion
{


public:
	Recepcion(std::string miDireccion, Buffer* _buffer);
	void operator() ();
	~Recepcion();
};


