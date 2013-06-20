#ifndef PREDICTOR_H_
#define PREDICTOR_H_

#include <iostream>
#include <list>
#include "Contexto.h"

using namespace std;



struct probabilidades {

	unsigned short int probaCaracter;
	unsigned short int probaAcumulada;
	unsigned short int probaTotal;

};


class Predictor
{
public:

	Predictor(unsigned short int orden);
	~Predictor();
	probabilidades getProbabilidad(char caracter);

private:

	unsigned short int orden;
	list<Contexto> listaContextos;

};

#endif
