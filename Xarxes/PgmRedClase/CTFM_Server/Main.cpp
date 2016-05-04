#pragma once
#include <SocketTools.h>
#include "Server.h"
#include "ListOfMonsters.h"
#include <GameConstants.h>
#include <time.h>
#include <UDPSocket.h>

bool ProcesarMensaje(ListOfMonsters& _monsters, std::string _messaje)
{
	int index_ = _messaje.find_first_of('_');
	std::string header = _messaje.substr(0, index_);
	std::string content = _messaje.substr(index_ + 1, _messaje.size() - index_);
	if (header == std::string(HEADER_POSITION))
	{
		//Comprobamos si hemos acertado a algún monstruo y actualizamos la lista
	}
	return false;
}

void ServerRun(std::string serverAddress)
{
	//TODO: Inicializamos un objeto servidor y esperamos a que lleguen los 2 jugadores (lo tenemos fijado a 2 desde GameConstants.h)
	//TODO: Una vez llegan los jugadores, ponemos el socket UDP a nonblocking
	//TODO: Enviamos BEGIN a todos los jugadores
	//TODO: Inicializamos una lista de monstruos que inicialmente será de MAX_MONSTERS (a medida que los maten será de menos)

	//TODO: Entramos en el bucle de servidor 

		//TODO: Si toca refrescar la posición de los monstruos, lo hacemos: Recordemos que cada cierto tiempo cambian de posición para tocar las narices.
			//TODO: Hemos de hacer gestión del tiempo: Usad la función clock() de la time.h
			//TODO: La nueva posición habrá que enviarla a todos los clientes
			//TODO: Si nos hemos quedado sin monstruos, enviar un END a todos los clientes
		//TODO: Revisamos si ha llegado algún mensaje de alguno de los clientes, si ha llegado algo: Lo proceso. 

	

}




int main(int argc, char** argv) {
	SocketTools::CargarLibreria();
	std::string serverAddress = argv[1];
	ServerRun(serverAddress);
	SocketTools::DescargarLibreria();
	system("pause");
	return 0;
}