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

void ListaExclusion::excluirCaracter(int a)
{
	exclusionesTemporales[a] = true;
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

bool ListaExclusion::estaExcluido(int caracter)
{
	return exclusiones[caracter];
}


void ListaExclusion::persistir()
{
	for (int i=1;i<MAX_CHARS;i++) {
		exclusiones[i] = exclusionesTemporales[i];
	}
}

void ListaExclusion::imprimir()
{
	std::cout<<"Inicio de impresion"<<std::endl;
	for (int i=1;i<MAX_CHARS;i++) {
		std::cout<<i<<" "<<exclusiones[1]<<std::endl;
	}
	std::cout<<"Fin de impresion"<<std::endl;
}
