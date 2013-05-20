//
//  TestArchivoBloques.h
//  Test2
//
//  Created by Federico Colangelo on 18/05/13.
//  Copyright (c) 2013 Federico Colangelo. All rights reserved.
//

#ifndef TestArchivoBloques_h
#define TestArchivoBloques_h

#include <iostream>
#include <fstream>
#include "../codigo/fisica_ArchivoBloques.h"

#define BLOCKSIZE 512

using namespace std;

struct ArchivoBloquesTestStruct {
    int unEntero;
    char* unString;
    int miCasa;
    int otraCasa;
};

class TestArchivoBloques
{
public:
    TestArchivoBloques();
    int test();
private:
    bool assertEquals(ArchivoBloquesTestStruct &unStruct, ArchivoBloquesTestStruct &otroStruct);
    
    
};

#endif 
