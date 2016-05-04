#include "NetworkClient.h"
#include "GameConstants.h"

NetworkClient::NetworkClient(std::string _serverAddress, std::string _nick, UserData* _userData) : nick(_nick)
{
	userData = _userData;
	SocketAddress sa;
	sa.SetAddress(_serverAddress);

	int err = tcpSocket.Connect(sa);
	if (err == -1)
	{
		throw std::exception("Error en connect");
	}
}


int NetworkClient::Receive(std::string & _message)
{
	char buffer[1300];
	int err = tcpSocket.Receive(buffer, 1300);
	if (err > 0 && err < 1300)
	{
		buffer[err] = '\0';
	}
	if (err > 0)
	{
		_message = buffer;
	}
	return err;
}

int NetworkClient::Send(std::string _message)
{
	int bytes = tcpSocket.Send(_message.c_str());
	return bytes;
}

void NetworkClient::ProcessMessage(std::string _message)
{
	int index_ = _message.find_first_of('_');
	std::string cabecera = _message.substr(0, index_);
	std::string contenido = _message.substr(index_ + 1, _message.size() - index_);

	if (cabecera == HEADER_BEGIN)
	{
		std::string strNickSend = "NICK_";
		strNickSend = strNickSend.append(nick);
		tcpSocket.Send(strNickSend.c_str());

		int err = tcpSocket.NonBlocking(true);
		if (err == -1)
		{
			throw std::exception("Error en nonblocking");
		}
		std::cout << "Empieza la partida." << std::endl;
	}
	else if (cabecera == HEADER_ROLE)
	{
		role = atoi(contenido.c_str());
		switch (role)
		{
		case PLAYER_ROLE_ASSASSIN:
			std::cout << "Eres el asesino." << std::endl;
			break;
		case PLAYER_ROLE_POLICE:
			std::cout << "Eres el policia." << std::endl;
			break;
		case PLAYER_ROLE_VICTIM:
			std::cout << "Eres una víctima potencial." << std::endl;
			break;
		}
	}
	else if (cabecera == HEADER_MSGSERVER || cabecera == HEADER_CHATNICK || cabecera == HEADER_PLAYERGAMESTATE)
	{
		std::cout << contenido << std::endl;
	}
	/*else if (cabecera == HEADER_CHATNICK)
	{
		std::cout << contenido << std::endl;
	}
	else if (cabecera == HEADER_PLAYERGAMESTATE)
	{
		std::cout << contenido << std::endl;
	}*/
}

NetworkClient::~NetworkClient()
{

}
