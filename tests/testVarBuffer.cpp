//
//  main.cpp
//  FileHandler
//
//  Created by Federico Colangelo on 21/04/13.
//  Copyright (c) 2013 Federico Colangelo. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "fisica_VarBuffer.h"

#define BUFFSIZE 128
#define TESTCASES 10

using namespace std;

struct testStruct {
    int unEntero;
    char* unString;
};

int assertEquals (testStruct &unStruct, testStruct &otroStruct)
{
    return (unStruct.unEntero==otroStruct.unEntero && unStruct.unString==otroStruct.unString);
    
}


int main(int argc, const char * argv[])
{     
    fstream outFile("testVarBuffer.dat",ios::out|ios::binary);
    
    cout<<outFile.tellp()<<endl;
    
    testStruct unTestStruct[TESTCASES];
    
    VarBuffer unBuffer(BUFFSIZE);
    
    srand(time(NULL));
    
    for (int i=0;i<TESTCASES;i++) {
        unTestStruct[i].unEntero=rand()%100;
        unTestStruct[i].unString=(char*)(rand()%10000);
        unBuffer.pack(&unTestStruct[i], sizeof(unTestStruct[i]));
        unBuffer.write(outFile);
        cout<<outFile.tellp()<<endl;
        
    }
    outFile.close();
    
    fstream inFile("testVarBuffer.dat",ios::in|ios::binary); 
    testStruct otroTestStruct;
    
    for (int i=0; i<TESTCASES; i++) {
        unBuffer.read(inFile);
        cout<<inFile.tellg()<<endl;
        unBuffer.unpack(&otroTestStruct);
        cout<<assertEquals(unTestStruct[i], otroTestStruct)<<endl;
        };
    inFile.close();
 
    return 0;
}