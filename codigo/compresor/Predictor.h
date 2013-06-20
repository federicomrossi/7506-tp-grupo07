#ifndef PREDICTOR_H_
#define PREDICTOR_H_

#include <iostream>
#include <list>
#include "Contexto.h"

using namespace std;


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
