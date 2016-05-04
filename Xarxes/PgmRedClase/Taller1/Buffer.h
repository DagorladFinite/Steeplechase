#pragma once
#include <string>
#include <mutex>


#define MAX_MENSAJES 10
#define WRITE_POS_X 1
#define WRITE_POS_Y 23
#define MENSAJES_POS_X 0
#define MENSAJES_POS_Y 1

class Buffer
{
private:
	std::string aMensajes[MAX_MENSAJES];
	std::mutex mMutex;
	int numMensajes;
	
public:
	Buffer();
	static void gotoxy(int x, int y);
	void Mostrar();
	void Encolar(char mensaje[]);
	~Buffer();
};

