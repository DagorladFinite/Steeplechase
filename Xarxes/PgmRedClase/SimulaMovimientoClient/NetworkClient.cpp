#include "NetworkClient.h"
#include <string>

//Al principio el estado de la red es UNINITIALIZED
NetworkClient::NetworkClient(std::string _addressServer, std::string _addressClient, std::string _nick):nick(_nick), networkState(NetworkState::UNINITIALIZED)
{
	saServer.SetAddress(_addressServer);
	SocketAddress myAddress;
	myAddress.SetAddress(_addressClient);
	int errBind = udpSocket.Bind(myAddress);
	int errBlock = udpSocket.NonBlocking(true);
	if (errBind > -1 && errBlock > -1)
	{
		//Si podemos hacer BIND y NONBLOCKING, pasamos a estado SAYINGHELLO
		//Este cliente empezará a buscar al servidor.
		networkState = NetworkState::SAYINGHELLO;
	}
}

NetworkState NetworkClient::GetNetworkState()
{
	return networkState;
}

void NetworkClient::SetNetworkState(NetworkState _networkState)
{
	networkState = _networkState;
}

int NetworkClient::GetIdSquare()
{
	return idSquare;
}

void NetworkClient::SetIdSquare(int _idSquare)
{
	idSquare = _idSquare;
}

void NetworkClient::SayHello()
{
	//Mientras esté en SAYING HELLO, iré enviado HELLOs cada FREQUENCY_SAYING_HELLO ms.
	if (networkState == NetworkState::SAYINGHELLO)
	{
		clock_t time = clock();
		if (time > timeOfLastHello + FREQUENCY_SAYING_HELLO)
		{
			std::string message = HEADER_HELLO;
			message = message.append("_" + nick);
			Send(message);
			timeOfLastHello = time;
		}
	}
}

void NetworkClient::SendCommand(InputState & _inputState)
{
	if (networkState == NetworkState::WELCOMED)
	{
		clock_t time = clock();
		if (time > timeOfLastMove + FREQUENCY_SENDING_COMMANDS)
		{
			if (_inputState.GetXs() != 0)
			{
				std::string message = std::string(HEADER_TRYPOSITION) + "_" + /*std::to_string(id) + "_" + */std::to_string(_inputState.GetXs());
				_inputState.Reset();
				Send(message);
			}
			timeOfLastMove = time;
		}
	}
}

void NetworkClient::Send(std::string _message)
{
	//std::cout << "Envío: " << _message.c_str() << std::endl;
	udpSocket.SendTo(_message.c_str(), _message.length(), saServer);
}

int NetworkClient::Receive(std::string& _message)
{
	char buffer[MAX_BUFFER];
	SocketAddress from;
	int bytesReceived = udpSocket.ReceiveFrom(buffer, MAX_BUFFER, from);
	if (bytesReceived > 0)
	{
		
		if (bytesReceived < MAX_BUFFER)
		{
			buffer[bytesReceived] = '\0';
		}
		_message = buffer;
	}
	return bytesReceived;
}





NetworkClient::~NetworkClient()
{
}
