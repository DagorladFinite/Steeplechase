#pragma once
#include "Comunicacion.h"

class Envio:public Comunicacion
{

public:
	Envio(std::string direccionDestino, Buffer* _buffer);
	void operator() ();
	
	~Envio();
};

