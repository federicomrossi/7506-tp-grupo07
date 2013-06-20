#ifndef PPMC_H_
#define PPMC_H_

#include <iostream>
#include <fstream>
#include "../compresion_Aritmetico.h"
// FALTA INCLUIR CONTEXTOS (POSIBLEMENTE PREDICTOR.H)

class PPMC
{
public:

	PPMC();
	~PPMC();
	int comprimir(fstream archivo);
	int descomprimir(fstream archivo);

private:

};

#endif
