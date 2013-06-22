#ifndef LISTAEXCLUSION_H_
#define LISTAEXCLUSION_H_

#define MAX_CHARS 257

#include <iostream>

class ListaExclusion
{

public:

	ListaExclusion();
	~ListaExclusion();
	void excluirCaracter(char caracter);
	bool estaExcluido(char caracter);
	void persistir();
	void reset();
	void imprimir();

private:

	bool exclusiones[MAX_CHARS];
	bool exclusionesTemporales[MAX_CHARS];
};


#endif
