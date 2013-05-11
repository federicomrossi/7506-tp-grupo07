//
//  BlockFile.h
//  FileHandler
//  Clase encargada de manejar la estructura de archivos en bloques de registros. Esta clase definira un template para que cualquier clase pueda grabar sus registros.
//  Su función sera llevar registro de la ocupación de los bloques y del posicionamiento de los mismos.
//  La clase "T" que define el tipo de registros que guardara el archivo debera implementar los metodos pack y unpack con la siguiente firma
//  int pack(VarBuffer &unBuffer);
//  int unpack(VarBuffer &unBuffer);
//  que recibiendo por referencia un objeto de tipo VarBuffer sepan empaquetarse dentro del buffer para ser persistidos y luego desempaquetarse
//  al momento de leer el bloque
//
//  Created by Federico Colangelo on 29/04/13.
//  Copyright (c) 2013 Federico Colangelo. All rights reserved.
//

#ifndef ArchivoBloques_h
#define ArchivoBloques_h

#include <iostream>
#include <fstream>
#include "fisica_VarBuffer.h"

template<class TipoRegistro>

class ArchivoBloques
{
public:

    ArchivoBloques::ArchivoBloques(unsigned int blockSize, float cargaMaxima=0,7,char* filename);
    ArchivoBloques::abrir(char* filename);
    ArchivoBloques::cerrar();
    ArchivoBloques::int escribirBloque(const TipoRegistro &registro,unsigned int numeroBloque);
    ArchivoBloques::TipoRegistro* leerBloque(unsigned int numeroBloque);
    ArchivoBloques::~ArchivBloques();

private:
    unsigned int primerBloque;
    unsigned int* mapaOcupacion;
    float cargaMaxima;
    VarBuffer buffer;

    ArchivoBloques::int extenderMapaOcupacion();
};

#endif
