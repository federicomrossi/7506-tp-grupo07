//
//  fisica_ArchivosBloques.cpp
//  FileHandler
//
//  Created by Federico Colangelo on 12/05/13.
//  Copyright (c) 2013 Federico Colangelo. All rights reserved.
//

#include "fisica_ArchivoBloques.h"

ArchivoBloques::ArchivoBloques(unsigned int blockSize, std::string filename)
{
    this->filename=filename;
    this->blockSize=blockSize;
}


void ArchivoBloques::borrarArchivo()
{
    remove(filename.c_str());
}


int ArchivoBloques::escribirBloque(const char *buffer, unsigned int numeroBloque)
{
    // Si el archivo no existe, escribimos directamente el dato
    if (!this->existe())
    {
       std::ofstream file;
       file.open(filename.c_str(), std::ios::out | std::ios::binary);

       file.seekp(numeroBloque * this->blockSize, std::fstream::beg);
       file.write(buffer, this->blockSize);

       file.close();

       return 0;
    }

    // Variables auxiliares
    std::ifstream file;
    std::ofstream tempFile;
    std::string tempFilename = this->filename+"~";
    unsigned int numBlocksToWrite;

    // Abrimos el archivo original y el archivo temporal
    file.open(this->filename.c_str(), std::ifstream::binary | std::ios::ate);
    tempFile.open(tempFilename.c_str(), std::fstream::out | std::fstream::app);

    // Calculamos la cantidad de bloques que hay en el archivo original
    int length = file.tellg();
    unsigned int numTotalBlocks = length / this->blockSize;

    // Comprobamos que numero de bloque debemos tomar como referencia.
    if(numTotalBlocks > numeroBloque)
        numBlocksToWrite = numTotalBlocks - 1;
    else
        numBlocksToWrite = numeroBloque;

    // Iteramos sobre los bloques del archivo original
    int pos=0;
    
    for(unsigned int i=0; i <= numBlocksToWrite; i++)
    {
        // Creamos buffer (BUSCAR MEJORARLO DECLARANDOLO AFUERA Y LIMPIANDOLO
        // EN CADA PASADA PARA MEJOR RENDIMIENTO)
        char* tempBuffer = new char[this->blockSize];
        
        // Caso en el que bloque en el que estamos es el que deseamos 
        // actualizar
        if(i == numeroBloque)
        {
            // Escribimos el dato nuevo en el archivo temporal
            tempFile.write(buffer, this->blockSize);
            delete [] tempBuffer;
            file.seekg(pos);
            pos += this->blockSize;
            continue;
        }

        // Copiamos contenido en el archivo temporal de a un bloque por vez
        file.seekg(pos);
        file.read(tempBuffer, this->blockSize);
        tempFile.write(tempBuffer, this->blockSize);
        pos += this->blockSize;
        
        // Eliminamos buffer
        delete [] tempBuffer;
    }

    tempFile.close();
    file.close();
    
    remove(this->filename.c_str());
    rename(tempFilename.c_str(),this->filename.c_str());

    return 0;
}

int ArchivoBloques::agregarBloque(const char *buffer)
{
   std::ofstream file;
   file.open(this->filename.c_str(),std::ios::app);
   file.write(buffer,this->blockSize);
   file.close();
   return 0;
}


int ArchivoBloques::leerBloque(char *buffer, unsigned int numeroBloque)
{
    std::ifstream file;
    file.open(this->filename.c_str());
    file.seekg(numeroBloque*this->blockSize,std::ios_base::beg);
    file.read(buffer, this->blockSize);
    file.close();
    return 0;
}

bool ArchivoBloques::existe()
{
    std::ifstream file;
    file.open(this->filename.c_str());
    bool existe = file.good();
    file.close();
    return existe;
}

int ArchivoBloques::ultimoBloque()
{
    std::ifstream file;
    if (!this->existe()) {
        std::cerr<<"El arhcivo no existe"<<std::endl;
        return -1;
    }
    
    file.open(this->filename.c_str());
    file.seekg(0,std::ios_base::end);
    int ultimoBloque=(file.tellg()/this->blockSize)-1;
    return ultimoBloque;
}

