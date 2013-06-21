#ifndef PPMC_H_
#define PPMC_H_

#include <iostream>
#include <fstream>
#include <string>
#include "Predictor.h"
// FALTA INCLUIR CONTEXTOS (POSIBLEMENTE PREDICTOR.H)

class PPMC
{
public:

	PPMC(unsigned short  int orden,std::string archivo);
	~PPMC();
	int comprimir(std::string archivoSource);
	int descomprimir(std::string archivoSource);

private:
    Predictor* predictor;
    unsigned short orden;
};

#endif
