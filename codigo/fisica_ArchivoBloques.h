//
//  BlockFile.h
//  EL PRIMER BLOQUE ES EL BLOQUE 1
//  Clase encargada de manejar la estructura de archivos en bloques de registros.
//  Su función sera llevar registro de la ocupación de los bloques y del posicionamiento de los mismos.
//  Para escribir en el archivo debera pasarse como argunmento un puntero a un objeto cualquiera y el numero de bloque en el cual escribirlo.
//  Para leer deberá pasarse el numero de bloque a leer y un puntero a un objeto cualquier en donde poner los datos leidos.
//  Created by Federico Colangelo on 29/04/13.
//  Copyright (c) 2013 Federico Colangelo. All rights reserved.
//

#ifndef fisica_ArchivoBloques_h
#define fisica_ArchivoBloques_h

#include <iostream>
#include <fstream>
//#include <string>

class ArchivoBloques
{
public:
    
    ArchivoBloques(unsigned int blockSize, std::string filename);
    
    /*Borra el archivo*/
    void borrarArchivo();
    
    /*
     // PRE: El archivo debe estar abierto y el tamaño de registro debe ser menor al del bloque-2bytes.
     // USO: El metodo escribir bloque utiliza la direccion de objeto que se le pasa para escribirlo en el bloque correspondiente.
     // POST: Se escribe el contenido del objeto en el bloque elegido. Devuelve -1 si el archivo no estaba abierto y <datosEscritos> en caso de haber escrito a disco.
     // Este metodo no cierra el arhcivo.
     */
    int escribirBloque(const char* buffer, unsigned int numeroBloque);
    
    /*
     // USO: La clase que desee utilizar el archivo por bloques debera pasar la direccion de un objeto en donde quiere que se lea la informacion.
     // POST: El metodo escribe el contenido del bloque en el objeto. Devuelve -1 si el archivo no estaba abierto y <datosLeidos> en caso de cargar el registro.
     // Este metodo no cierra el archivo.
     */
    int leerBloque(char* buffer, unsigned int numeroBloque);
    
    bool existe();
    
    int ultimoBloque();
    
    
    
private:
    unsigned int blockSize;
    std::string filename;
    
};

#endif
