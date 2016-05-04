#include "NetworkClient.h"


NetworkClient::NetworkClient(std::string _addressServer, std::string _addressClient, std::string _nick):nick(_nick), networkState(NetworkState::UNINITIALIZED)
{
	saServer.SetAddress(_addressServer);
	SocketAddress myAddress;
	myAddress.SetAddress(_addressClient);
	int errBind = udpSocket.Bind(myAddress);
	int errBlock = udpSocket.NonBlocking(true);
	if (errBind > -1 && errBlock > -1)
	{
		//std::cout << "El estado de cliente pasa a SAYING HELLO" << std::endl;
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
	clock_t time = clock();
	if (time > timeOfLastHello + FREQUENCY_SAYING_HELLO)
	{
		std::string message = HEADER_HELLO;
		message = message.append("_"+nick);
		Send(message);
		timeOfLastHello = time;
	}
}

void NetworkClient::SendMove(int _positionSquare, InputState& _inputState, InputStateList& _inputStateList)
{
	clock_t time = clock();
	if (time > timeOfLastMove + FREQUENCY_SENDING_INPUTS)
	{
		std::string move;
		_inputState.SetId(_inputStateList.GetCounter());
		bool okSend = _inputState.Serialize(move);
		
		if (okSend)
		{
			_inputState.SetAbsolutePosition(_positionSquare);
			
			std::cout << "Envío a servidor " << move << "; Cuadrado en: " << _positionSquare << std::endl;
			_inputStateList.Add(_inputState);
			Send(move);
			_inputState.ResetMove();
		}
		timeOfLastMove = time;
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
