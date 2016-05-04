#include "UserInput.h"

//UserData es un puntero a la estructura dónde se copian los datos
//que escribe el jugador desde consola.
//Es un puntero porque se comparte desde otro proceso.
UserInput::UserInput(UserData * userData)
{
	this->userData = userData;
}

//Sencillamente, pide por consola y retorna un string con lo que ha 
//escrito el jugador
std::string UserInput::PideDatosTeclado()
{
	std::string strDatos;
	std::getline(std::cin, strDatos);
	int longitud = strDatos.length();
	return strDatos;
}

//Esta es la función que se llama cuando lanzamos el thread.
//Cada vez que el jugador escribe una nueva palabra, dejamos
//preparado el mensaje WRITE_palabra, para enviar a servidor.
void UserInput::operator()()
{
	while (true)
	{
		std::string input = PideDatosTeclado();
		std::string sending = "WRITE_";
		sending.append(input);
		userData->SetWord(input);
	}
}

UserInput::~UserInput()
{
}
