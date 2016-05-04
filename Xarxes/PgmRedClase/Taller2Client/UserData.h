#pragma once
#include <string>
#include <mutex>

class UserData
{
private:
	std::string word;
	bool sent;
	std::mutex mtx;

public:
	UserData():sent(true)
	{
	}

	//Copiamos la palabra que ha escrito el jugador.
	//Mientras la copiamos, bloqueamos el string para que no se pueda
	//estar enviando a la vez.
	//Para que sepamos que esta palabra es nueva y que aun no se ha enviado
	//ponemos sent a false.
	void SetWord(std::string _word)
	{
		mtx.lock();
		this->word = _word;
		sent = false;
		mtx.unlock();
	}

	//Para obtener la palabra que hay que enviar
	//Si no hay que enviar ninguna palabra porque ya se ha enviado antes
	//se retorna false.
	//Si hay que enviar la palabra, se retorna true y copiamos en _word
	//la palabra que hay que enviar.
	//Mientras hacemos esta consulta, también debemos bloquear el recurso,
	//para que el thread de escritura no lo esté sobrescribiendo a la vez.
	bool GetWord(std::string& _word)
	{
		bool ret;
		mtx.lock();
		if (sent)
		{
			ret = false;
		}
		else
		{
			_word = word;
			sent = true;
			ret = true;
		}
		mtx.unlock();
		return ret;
	}

	~UserData() {}
};


