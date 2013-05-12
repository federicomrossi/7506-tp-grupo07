//
//  fisica_ArchivosBloques.cpp
//  FileHandler
//
//  Created by Federico Colangelo on 12/05/13.
//  Copyright (c) 2013 Federico Colangelo. All rights reserved.
//

#include "fisica_ArchivoBloques.h"

ArchivoBloques::ArchivoBloques(unsigned int blockSize,const char* filename) : IOBuffer(blockSize)
{
    this->filename=filename;
    this->blockSize=blockSize;
}


int ArchivoBloques::crearArchivo()
{
    this->file.open(this->filename, ios::in|ios::binary);
    
    if (this->file.good()) {
        this->file.close();
        this->file.open(this->filename,ios::trunc|ios::binary);
        this->file.close();
        return 1;
    } else {
        this->file.close();
        this->file.open(this->filename, ios::out|ios::binary);
        this->file.close();
        return 0;
    }

}


int ArchivoBloques::abrirArchivo()
{
    this->file.open(this->filename, ios::in|ios::binary);
    
    if (this->file.good()) {
        this->file.close();
        this->file.open(this->filename,ios::in|ios::out|ios::binary);
        return 0;
    } else return -1;
}


void ArchivoBloques::cerrarArchivo()
{
    this->file.close();
}

bool ArchivoBloques::estaAbierto()
{
    return this->file.is_open();
}



