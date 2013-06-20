#include "ListaExclusion.h"

ListaExclusion::ListaExclusion() 
{
	this->reset();
}

ListaExclusion::~ListaExclusion() {}


void ListaExclusion::excluirCaracter(char a)
{
	exclusionesTemporales[(int)a] = true;
}


void ListaExclusion::reset()
{
	for (int i=0; i<MAX_CHARS;i++) {
		exclusiones[i] = false;
	}

	for (int i=0; i<MAX_CHARS;i++) {
		exclusionesTemporales[i] = false;
	}
}


bool ListaExclusion::estaExcluido(char caracter)
{
	return exclusiones[(int)caracter];
}


void ListaExclusion::persistir()
{
	for (int i=1;i<MAX_CHARS;i++) {
		exclusiones[i] = exclusionesTemporales[i];
	}
}
