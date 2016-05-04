#pragma once
#include <memory>
#include <iostream>
#include <SocketTools.h>
#include "Recepcion.h"
#include "Envio.h"


int16_t miPuertoRead;
int16_t remotoPuerto;

void run(std::string miDireccion, std::string direccionRemota)
{
	Buffer buffer;
	Envio escritura(direccionRemota, &buffer);
	Recepcion lectura(miDireccion, &buffer);

	std::thread tWrite(escritura);
	std::thread tRead(lectura);

	tWrite.join();
	tRead.join();
}

int main(int argc, char** argv)
{
	SocketTools::CargarLibreria();
	std::string miDireccion = argv[1];
	std::string direccionRemota = argv[2];

	run(miDireccion, direccionRemota);
	
	
	SocketTools::DescargarLibreria();
	system("pause");
}


