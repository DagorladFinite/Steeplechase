#include "UserInput.h"
#include "GameConstants.h"

std::string UserInput::PideDatosTeclado()
{
	std::string strDatos;
	std::getline(std::cin, strDatos);
	int longitud = strDatos.length();


	return strDatos;
}


UserInput::UserInput(UserData * userData)
{
	this->userData = userData;
}

void UserInput::operator()()
{
	while (true)
	{
		std::string input = PideDatosTeclado();
		int index_ = input.find_first_of('_');
		std::string cabecera = input.substr(0, index_);
		if (cabecera != HEADER_KILL && cabecera != HEADER_CATCHYOU && cabecera != HEADER_RESEND)
		{
			input = "CHAT_" + input;
		}
		userData->SetMessage(input);
	}
}

UserInput::~UserInput()
{
}