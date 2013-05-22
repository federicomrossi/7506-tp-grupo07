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
    std::ofstream file;
    file.open(this->filename.c_str(),std::ios::out|std::ios::binary|std::ios::app);
    file.seekp(numeroBloque*this->blockSize,file.beg);
    file.write(buffer, this->blockSize);
    std::cout<<"Escribi hasta el "<<file.tellp()<<std::endl;
    file.close();
    return 0;
}


int ArchivoBloques::leerBloque(char *buffer, unsigned int numeroBloque)
{
    std::ifstream file;
    file.open(this->filename.c_str(),std::ios::in|std::ios::binary);
    file.seekg(numeroBloque*this->blockSize,file.beg);
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

