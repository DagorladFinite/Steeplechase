#pragma once
#include <iostream>
#include "UserData.h"

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

