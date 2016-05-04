#include "SocketAddress.h"

int main()
{
	SocketAddress a(127, 0, 0, 1, 80);
	SocketAddress b(a);
	return 0;
}