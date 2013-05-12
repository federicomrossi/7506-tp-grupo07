//
//  BlockFile.h
//  EL PRIMER BLOQUE ES EL BLOQUE 1
//  Clase encargada de manejar la estructura de archivos en bloques de registros.
//  Su función sera llevar registro de la ocupación de los bloques y del posicionamiento de los mismos.
//  Para escribir en el archivo debera pasarse como argunmento un objeto VarBuffer y el numero de bloque en el cual escribirlo.
//  Para leer deberá pasarse el numero de bloque a leer y un VarBuffer en donde poner los datos leidos.
//  Created by Federico Colangelo on 29/04/13.
//  Copyright (c) 2013 Federico Colangelo. All rights reserved.
//

#ifndef fisica_ArchivoBloques_h
#define fisica_ArchivoBloques_h

#include <iostream>
#include <fstream>
#include "fisica_VarBuffer.h"

class ArchivoBloques
{
public:

    ArchivoBloques(unsigned int blockSize, char* filename);
    
    void cerrar();
    
    /*
    // PRE: El tamano del VarBuffer debera ser menor o igual al tamaño del bloque.
    // USO: El metodo escribir bloque utiliza el VarBuffer que es le pasa por referencia para escribirlo en el bloque correspondiente.
    // Para ello previamente debe empaquetarse el contenido a guardar en el bloque dentro de un VarBuffer mediante metodos de dicha clase.
    // POST: Se escribe el contenido de VarBuffer en el bloque elegido.
    // Este metodo no cierra el arhcivo.
    */
    int escribirBloque(const VarBuffer &bloque, unsigned int numeroBloque);
    
    /*
    // PRE: El tamano de VarBuffer debera ser mayor o igual que el del bloque
    // USO: La clase que desee utilizar el archivo por bloques deberá pasar el VarBuffer donde quiere que se lea la informacion.
    // POST: El metodo escribe el contenido del bloque en VarBuffer
    // Este metodo no cierra el archivo.
    */
    int leerBloque(VarBuffer &bloque, unsigned int numeroBloque);
    
    ~ArchivoBloques();

private:
    unsigned int blockSize;
    unsigned short int primerBloque;
    char* filename;

    //int extenderMapaOcupacion();
};

#endif
