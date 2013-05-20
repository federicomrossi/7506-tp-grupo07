//
//  TestVarBuffer.h
//  Test2
//
//  Created by Federico Colangelo on 18/05/13.
//  Copyright (c) 2013 Federico Colangelo. All rights reserved.
//

#ifndef TestVarBuffer_h
#define TestVarBuffer_h
#define BUFFSIZE 128
#define TESTCASES 10

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "../codigo/fisica_VarBuffer.h"

using namespace std;

struct VarBufferTestStruct {
    int unEntero;
    char* unString;
    bool unBool;
};

class TestVarBuffer
{
public:
    TestVarBuffer();
    int test();
    
private:
    bool assertEquals(VarBufferTestStruct &unStruct, VarBufferTestStruct &otroStruct);
};


#endif
