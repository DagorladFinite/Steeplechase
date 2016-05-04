#include "NetworkManager.h"


NetworkManager::NetworkManager(std::string _serverAddress, std::string _nick, UserData* _userData) : nick(_nick)
{
	userData = _userData;
	//Hago un connect a la dirección del servidor.

	SocketAddress sa;
	sa.SetAddress(_serverAddress);

	int err = tcpSocket.Connect(sa);
	if (err == -1)
	{
		throw std::exception("Error en connect");
	}
}

int NetworkManager::Receive(std::string & _message)
{
	//Recibo a través del tcpSocket.
	//Copio en _message el texto recibido.
	//Retorno el número de bytes recibidos.
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

int NetworkManager::Send(std::string _message)
{
	//Envío a servidor el mensaje indicado.
	//Retorno el número de bytes enviados.
	int bytes = tcpSocket.Send(_message.c_str());
	return bytes;
}

void NetworkManager::ProcessMessage(std::string _message)
{
	int index_ = _message.find_first_of('_');
	std::string cabecera = _message.substr(0, index_);
	std::string contenido = _message.substr(index_ + 1, _message.size() - index_);

	//A un jugador le pueden llegar estos tipos de mensajes:
	//Tipo 1: BEGIN
	//Tipo 2: WORD_palabraacopiar
	//Tipo 3: KOWORD
	//Tipo 4: OKWORD_nick, nick del que ha acertado
	//Tipo 5: SCORE_rankingformatado

	if (cabecera == "BEGIN")
	{
		//El juego empieza
		//Le envío al servidor mi nick: NICK_minick
		//Pongo el socket a nonblocking.
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
	else if (cabecera == "WORD")
	{
		//Me guardo en el atributo wordToCopy la palabra a copiar.
		wordToCopy = contenido;
		std::cout << "Escribe: " << wordToCopy << std::endl;
	}
	else if (cabecera == "KOWORD")
	{
		//Muestro el mensaje de que el jugador se ha equivocado.
		std::cout << "Te has equivocado." << std::endl;
		std::cout << "Escribe: " << wordToCopy << std::endl;
	}
	else if (cabecera == "OKWORD")
	{
		//Si el nick coincide con el del jugador, muestro un mensaje de que ha acertado.
		//Si el nick no coincide con el del jugador, muestro un mensaje de que
		// le ganó otro jugador.
		if (contenido == nick)
		{
			std::cout << "Acertaste, " << nick << std::endl;
		}
		else
		{
			std::cout << "Te ganó " << contenido << std::endl;
		}
	}
	else if (cabecera == "SCORE")
	{
		//Mostrar el ranking
		std::cout << "Ranking actual: " << contenido << std::endl;
	}
}

NetworkManager::~NetworkManager()
{
}
