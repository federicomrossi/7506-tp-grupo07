//
//  fisica_SerialBuffer.h
//  Clase utilizada para serializar varios elementos con iguales o distintos tipos
//  dentro de un buffer para su posterior escritura a disco. Extienden a VarBuffer
//  para poder manejar mas e un elemento por empaquetado.
//
//  Created by Federico Colangelo on 20/05/13.
//  Copyright (c) 2013 Federico Colangelo. All rights reserved.
//

#ifndef fisica_SerialBuffer_h
#define fisica_SerialBuffer_h

#include <iostream>
#include <string.h>
#include "fisica_VarBuffer.h"

class SerialBuffer : public VarBuffer
{
public:
    SerialBuffer(unsigned int maxSize);
    ~SerialBuffer();
    void clear();
    int pack(const void *object, unsigned short int size);
    int unpack(void *objetc);
    
private:
    unsigned int ultimoLeido;
    
};

#endif
