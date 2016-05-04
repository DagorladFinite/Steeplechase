#include "Buffer.h"
#include <iostream>
#include <Windows.h>


Buffer::Buffer()
{
	numMensajes = 0;
}



void Buffer::Mostrar()
{
	system("cls");
	mMutex.lock();
	Buffer::gotoxy(MENSAJES_POS_X, MENSAJES_POS_Y);
	for (int i = 0; i < numMensajes; i++)
	{
		std::cout << ">>" << aMensajes[i] << std::endl;
	}
	Buffer::gotoxy(WRITE_POS_X, WRITE_POS_Y);
	mMutex.unlock();
}

void Buffer::Encolar(char mensaje[])
{
	std::string str = mensaje;
	mMutex.lock();
	if (numMensajes == MAX_MENSAJES)
	{
		for (int i = 1; i < MAX_MENSAJES; i++)
		{
			aMensajes[i - 1] = aMensajes[i];
		}
		aMensajes[MAX_MENSAJES - 1] = str;
	}
	else
	{
		aMensajes[numMensajes] = str;
		numMensajes++;
	}
	mMutex.unlock();
}


void Buffer::gotoxy(int x, int y)
{
	COORD c = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

Buffer::~Buffer()
{
}
