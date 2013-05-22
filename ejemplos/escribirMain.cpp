//
//  main.cpp
//  FileHandler
//
//  Created by Federico Colangelo on 21/04/13.
//  Copyright (c) 2013 Federico Colangelo. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "fisica_SerialBuffer.h"
#include "fisica_ArchivoBloques.h"


int main(int argc, const char * argv[])
{
    ArchivoBloques file(10,"test");
    SerialBuffer unSerBuff(10);

    char a='a';
    int b=2;

    int c=65;
    char d='U'; 
    
 
    //guardo las cosas en el buffer
    unSerBuff.pack(&a, sizeof(a));
    unSerBuff.pack(&b, sizeof(b));
    //unSerBuff.pack(&e, sizeof(e));
    file.escribirBloque(unSerBuff.getBuffer(), 0);
    unSerBuff.clear();
   
    unSerBuff.pack(&c, sizeof(c));
    unSerBuff.pack(&d, sizeof(d));
    file.escribirBloque(unSerBuff.getBuffer(), 1); 
    unSerBuff.clear();
    

 
    return 0;
}
