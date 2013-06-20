#ifndef PREDICTOR_H_
#define PREDICTOR_H_

#include <iostream>
#include <list>
#include "Contexto.h"
#include "compresion_Aritmetico.h"

using namespace std;


class Predictor
{
public:

	Predictor(unsigned short int orden,std::string archivoDest);
	~Predictor();
	int comprimir(char caracter,std::string contextoActual);
	int finalizarCompresion(std::string contextoActual);
	int inicializarDescompresion();
	int descomprimir(std::string contextoActual);


private:
    ListaExclusion* listaExclusion;
    Aritmetico* aritmetico;
	unsigned short int orden;
	list<Contexto*>* listaContextos;

};

#endif
