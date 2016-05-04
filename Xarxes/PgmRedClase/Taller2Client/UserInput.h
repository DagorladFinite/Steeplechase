#pragma once
#include <iostream>
#include "UserData.h"

//Esta clase la usaremos para el thread que pide por teclado al jugador
//Como la entrada de usuario, bloquea el thread principal, lo preparamos
//para que sea un thread y no nos moleste.
class UserInput
{
private:
	UserData* userData;
	std::string PideDatosTeclado();

public:
	UserInput(UserData* userData);
	void operator()();
	~UserInput();
};

