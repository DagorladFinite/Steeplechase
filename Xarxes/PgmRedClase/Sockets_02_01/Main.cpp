#include "GenericSocket.h"
#include "SocketTools.h"

void test()
{
	SocketAddress addr;
	addr.SetAddress("localhost:5000");
	GenericSocket genSock(SOCK_DGRAM);
	genSock.Bind(addr);
}

int main()
{
	SocketTools::CargarLibreria();
	test();
	SocketTools::DescargarLibreria();
	system("pause");
}