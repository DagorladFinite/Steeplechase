#include "UDPSocket.h"
#include "SocketTools.h"


UDPSocket::UDPSocket():GenericSocket(SOCK_DGRAM)
{
}

int UDPSocket::SendTo(const void * data, int lenData, SocketAddress & to)
{
	sockaddr sa;
	to.GetAddress(sa);
	int numBytesSend = sendto(sock, (const char*)data, lenData, 0, &sa, sizeof(sockaddr));
	if (numBytesSend >= 0)
	{
		return numBytesSend;
	}
	else
	{
		SocketTools::MostrarError("Error en UDPSocket::SendTo");
		return -1;
	}
}

int UDPSocket::ReceiveFrom(void * data, int lenData, SocketAddress & from)
{
	sockaddr sa;
	int sizeFrom;
	int numBytesReceived = recvfrom(sock, (char*)data, lenData, 0, &sa, &sizeFrom);
	if (numBytesReceived >= 0)
	{
		return numBytesReceived;
	}
	else
	{
		SocketTools::MostrarError("Error en UDPSocket::ReceiveFrom");
		return -1;
	}
}


UDPSocket::~UDPSocket()
{
}
