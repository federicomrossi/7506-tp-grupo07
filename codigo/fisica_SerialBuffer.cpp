//
//  fisica_SerialBuffer.cpp
//  Test2
//
//  Created by Federico Colangelo on 20/05/13.
//  Copyright (c) 2013 Federico Colangelo. All rights reserved.
//

#include "fisica_SerialBuffer.h"

SerialBuffer::SerialBuffer(unsigned int maxSize) : VarBuffer(maxSize)
{
    this->ultimoLeido=0;
}

SerialBuffer::~SerialBuffer()
{
    //Solo hace falta el destructor de la clase padre
}

void SerialBuffer::clear()
{
    this->bufferSize=0;
    this->ultimoLeido=0;
}

int SerialBuffer::pack(const void *object, unsigned short int size)
{
    if (this->bufferSize+size > this->maxSize) {
        cerr<<"Se excede el tamano maximo del buffer";
        return -3;
    } 
    memcpy(&buffer[this->bufferSize], &size, sizeof(size));
    this->bufferSize+=sizeof(size);
    memcpy(&buffer[this->bufferSize], object, size);
    this->bufferSize+=size;
    return 0;
}

int SerialBuffer::unpack(void *objetc)
{
    unsigned short int readSize;
    memcpy(&readSize, &buffer[this->ultimoLeido], sizeof(readSize));
    this->ultimoLeido+=sizeof(readSize);
    memcpy(objetc, &buffer[this->ultimoLeido], readSize);
    this->ultimoLeido+=readSize;
    return 0;
}