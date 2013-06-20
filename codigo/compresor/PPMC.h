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

	PPMC(int orden);
	~PPMC();
	int comprimir(std::string archivoSource);
	int descomprimir(std::string archivoSource);

private:
    Predictor* predictor;
};

#endif
