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

/*  Metodo para limpiar el buffer luego de un proceso completo de escritura/lectura.
*/

void SerialBuffer::clear()
{
    this->bufferSize=0;
    this->ultimoLeido=0;
}

/*  Metodo para empaquetar objetos dentro de un buffer para su posterior escritura
//  a disco. Devuelve 0 en caso de empaquetarse correctamente y -3 en caso que no
//  hubiera espacio suficiente en el buffer.
//  PRE: el tamano del objeto a empaquetar debe ser al menos 2 bytes menor que el
//  espacio libre en el buffer.
//  POST: se agrega el objeto al buffer junto a su prefijo de longitud y se deja
//  asentado el espacio ocupado del buffer.
*/
 
int SerialBuffer::pack(const void *object, unsigned short int size)
{
    if (this->bufferSize+size+sizeof(size) > this->maxSize) {
        cerr<<"Se excede el tamano maximo del buffer";
        return -3;
    } 
    memcpy(&buffer[this->bufferSize], &size, sizeof(size));
    this->bufferSize+=sizeof(size);
    memcpy(&buffer[this->bufferSize], object, size);
    this->bufferSize+=size;
    return 0;
}
 
/*  Metodo para desempaquetar objetos dentro desde un buffer.
//  hubiera espacio suficiente en el buffer.
//  PRE: el objeto a desempaquetar debe ser del mismo tipo que el pasado como
//  argumento.
//  POST: Se restauran los valores del objeto en disco al objeto en memoria y se
//  deja asentada la cantidad leida.
*/

int SerialBuffer::unpack(void *objetc)
{
    unsigned short int readSize;
    memcpy(&readSize, &buffer[this->ultimoLeido], sizeof(readSize));
    this->ultimoLeido+=sizeof(readSize);
    memcpy(objetc, &buffer[this->ultimoLeido], readSize);
    this->ultimoLeido+=readSize;
    return 0;
}
