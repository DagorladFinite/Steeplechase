#include "ListaHabilidades.h"


int main()
{
	Habilidad h("Porrazo", 1);
	Habilidad h2("Grito", 2);

	ListaHabilidades lista;
	lista.Add(h);
	lista.Add(h2);
	lista.Add("Furia", 3);

	std::cout << lista[2];

	std::cout << lista;

	lista.Delete(h2);
	lista.Delete(0);

	std::cout << lista;

	system("pause");



}