#include "ListWords.h"



ListWords::ListWords():indexWord(0)
{
}

void ListWords::LoadFromFile(std::string nameFile)
{
}

void ListWords::LoadDefault()
{
	aWords.push_back("palabra1");
	aSent.push_back(false);
	aWords.push_back("palabra2");
	aSent.push_back(false);
	aWords.push_back("palabra3");
	aSent.push_back(false);
	//aWords.push_back("palabra4");
	//aSent.push_back(false);
	//aWords.push_back("palabra5");
	//aSent.push_back(false);
	//aWords.push_back("palabra6");
	//aSent.push_back(false);
	//aWords.push_back("palabra7");
	//aSent.push_back(false);
	//aWords.push_back("palabra8");
	//aSent.push_back(false);
	//aWords.push_back("palabra9");
	//aSent.push_back(false);
	//aWords.push_back("palabra10");
	//aSent.push_back(false);
}

/*
 * _word: Se copia la palabra que hay que enviar, en el caso de que haya que enviar alguna
 * retorna true si la palabra que toca enviar ya se ha enviado. 
 * retorna false si la palabra que toca enviar aún no se ha enviado (debemos enviarla)
 */
bool ListWords::WordToSend(std::string& _word)
{
	if (indexWord == aWords.size() || aSent[indexWord] == true)
	{
		return true;
	}
	else
	{
		_word = aWords[indexWord];
		return false;
	}
}

/**
 * Marca la palabra actual como enviada.
 */
void ListWords::WordSent()
{
	aSent[indexWord] = true;
}

/**
 *	Retorna true si _word es igual a la palabra que toca copiar ahora mismo.
 */
bool ListWords::Compare(std::string _word)
{
	return _word == aWords[indexWord];
}

/**
 *	Incrementamos el índice de la palabra que toca enviar. 
 *  Si hemos llegado al final del array de palabras, retornamos true.
 *  Si no retornamos false.
 */
bool ListWords::IncIndex()
{
	indexWord++;
	if (indexWord == aWords.size())
	{
		return true;
	}
	return false;
}

/**
 *	Retorna true 
 *  
 *  
*/
bool ListWords::EndList()
{
	return indexWord == aWords.size();
}

ListWords::~ListWords()
{
}
