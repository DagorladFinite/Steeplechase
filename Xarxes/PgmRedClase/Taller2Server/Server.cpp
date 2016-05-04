#include "Server.h"
#include "List.h"

Server::Server(std::string _serverAddress, int _numPlayers)
{
	aWords.LoadDefault();
	//Inicializar el socket de dispatcher

	//Ponerlo a Bind y a Listen

	SocketAddress sa;
	sa.SetAddress(_serverAddress);
	int err = dispatcher.Bind(sa);
	if (err == -1)
	{
		throw std::exception("Error en Server::Server");
	}
	err = dispatcher.Listen(_numPlayers);
	if (err == -1)
	{
		throw std::exception("Error en listen");
	}
}

void Server::LoadingPlayers(int _numPlayers)
{
	for (int i = 0; i < _numPlayers; i++)
	{
		//Esperar a que se conecten los _numPlayers jugadores.
		//Los esperaremos con un Accept.
		//Dejaremos el socket de dispatcher a blocking, para que el juego no 
		//empiece hasta que lleguen estos _numPlayers jugadores.

		//Cada uno de los jugadores que nos van llegando, los hemos de guardar en 
		//un ClientProxy.
		//Recordemos que el Accept des socket de dispatcher nos retorna un nuevo socket
		//que sirve para comunicar única y exclusivamente este jugador con el servidor.
		//Este nuevo socket lo pondremos a nonblocking, porque no quiero que el programa
		//se me quede bloqueado cada vez que espero recibir algo de este jugador.

		ClientProxy client;
		SocketAddress from;
		std::cout << "Esperando cliente " << (i + 1) << std::endl;
		std::shared_ptr<TCPSocket> tcpSocket = dispatcher.Accept(from);
		tcpSocket->NonBlocking(true);
		client.SetSocket(tcpSocket);
		aClients.push_back(client);
		std::cout << "Llega cliente " << (i + 1) << std::endl;
	}

	//Una vez han llegado todos los jugadores, les envío a todos un BEGIN
	//Recuerda que ya tienes una función que te permite enviar un mensaje a todos.
	SendMsgAll("BEGIN");
	std::cout << "Empieza el juego" << std::endl;
	
}

void Server::SendMsgAll(std::string _message)
{
	//Se debe enviar este mensaje a todos los jugadores
	//del vector aClients.
	for (int i = 0; i < aClients.size(); i++)
	{
		int err = aClients[i].Send(_message);
		if (err == -1)
		{
			std::cout << "Error al enviar al cliente " << i << std::endl;
		}
	}
}

void Server::ReceiveAndProcessMsgClients()
{
	//Por cada uno de los clientes que tenemos en aClients
	//Debo comprobar si me ha enviado algún mensaje (receive)
	//Si el mensaje que me llega tiene longitud 0, significa que el jugador se ha desconectado y lo puedo eliminar del vector aClients
	//Sino, proceso el mensaje que me llega utilizando la función ProcessMessage.
	
	for (int i = 0; i < aClients.size(); i++)
	{
		std::string message;
		int err = aClients[i].Receive(message);
		if (err == 0)
		{
			aClients.erase(aClients.begin() + i);
		}
		else if (err > 0)
		{
			bool exit = ProcessMessage(message, i);
			if (exit)
			{
				aClients.erase(aClients.begin() + i);
			}
		}
	}
}

bool Server::ProcessMessage(std::string _message, int _numClient)
{
	//Al servidor, le pueden llegar 2 tipos de mensajes: 
	//Tipo 1: NICK_
	//Tipo 2: WRITE_
	
	int index_ = _message.find_first_of('_');
	std::string cabecera = _message.substr(0, index_);
	std::string contenido = _message.substr(index_ + 1, _message.size() - index_);
	if (cabecera == "NICK")
	{
		//Sencillamente debemos guardar este mensajes en el ClientProxy que toque
		aClients[_numClient].SetNick(contenido);
	}
	else if (cabecera == "WRITE")
	{
		//Debo comprobar si la palabra que me envía el jugador es igual a la que toca escribir ahora o no.
		//Si NO son iguales, envío al cliente que ha fallado un KOWORD
		//Si son iguales, envío a todos los clientes un OKWORK_nickganador
		//En caso de haber acertado la palabra, debo incrementar el índice de la palabra que toca enviar.
		//Si ya hemos llegado a la última palabra, retornamos true, que significa que el juego ya ha acabado.
		bool equals = aWords.Compare(contenido);
		if (!equals)
		{
			aClients[_numClient].Send("KOWORD");
		}
		else
		{
			std::string msgSend = "OKWORD_";
			msgSend = msgSend.append(aClients[_numClient].GetNick());
			aClients[_numClient].AddScore();
			SendMsgAll(msgSend);
			msgSend = CreateMsgRanking();
			SendMsgAll(msgSend);
			bool endWords = aWords.IncIndex();
			if (endWords)
			{
				return true;
			}
		}
	}
	return false;
}

bool Server::SendWord()
{
	//Miramos qué palabra toca enviar ahora y si se ha enviado.
	//Si no se ha enviado, enviamos a todos los jugadores "WORD_palabraacopiar"
	//Si la palabra ya se ha enviado y estamos al final de la lista retornamos true. False, en caso contrario.

	std::string word;
	bool seHaEnviado = aWords.WordToSend(word);
	if (!seHaEnviado)
	{
		aWords.WordSent();
		std::string wordToSent = "WORD_";
		wordToSent = wordToSent.append(word);
		//std::cout << "Envío la palabra " << wordToSent << std::endl;
		SendMsgAll(wordToSent);
	}
	else if (aWords.EndList())
	{
		return true;
	}
	return false;
}

std::string Server::CreateMsgRanking()
{
	std::string ranking = "SCORE_";

	List<int> aIndicesMarcados;

	for (size_t j = 0; j < aClients.size(); j++)
	{
		int max = -1;
		int indexMax = -1;
		for (int i = 0; i < aClients.size(); i++)
		{
			int scoreAct = aClients[i].GetScore();
			if (scoreAct > max)
			{
				if (aIndicesMarcados.IndexOf(i) == -1)
				{
					max = scoreAct;
					indexMax = i;
				}
			}
		}
		aIndicesMarcados.push_back(indexMax);
		std::string nick = aClients[indexMax].GetNick();
		int score = aClients[indexMax].GetScore();
		ranking = ranking.append(nick);
		ranking = ranking.append(":");
		ranking = ranking.append(std::to_string(score));
		if (j < aClients.size() - 1)
		{
			ranking = ranking.append("#");
		}
	}
	return ranking;
}

Server::~Server()
{

}