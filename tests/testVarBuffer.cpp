//
//  TestVarBuffer.cpp
//  Test2
//
//  Created by Federico Colangelo on 18/05/13.
//  Copyright (c) 2013 Federico Colangelo. All rights reserved.
//

#include "TestVarBuffer.h"

TestVarBuffer::TestVarBuffer()
{
    
}

bool TestVarBuffer::assertEquals(VarBufferTestStruct &unStruct, VarBufferTestStruct &otroStruct)
{
    return (unStruct.unEntero==otroStruct.unEntero && unStruct.unString==otroStruct.unString && unStruct.unBool==otroStruct.unBool);
}

int TestVarBuffer::test()
{
    fstream outFile("testVarBuffer.dat",ios::out|ios::binary);
        
    VarBufferTestStruct unTestStruct[TESTCASES];
    
    VarBuffer unBuffer(BUFFSIZE);
    
    srand((unsigned int)time(NULL));
    
    for (int i=0;i<TESTCASES;i++) {
        unTestStruct[i].unEntero=rand()%100;
        unTestStruct[i].unString=(char*)(rand()%10000);
        unBuffer.pack(&unTestStruct[i], sizeof(unTestStruct[i]));
        unBuffer.write(outFile);        
    }
    outFile.close();
    
    fstream inFile("testVarBuffer.dat",ios::in|ios::binary);
    VarBufferTestStruct otroTestStruct;
    
    for (int i=0; i<TESTCASES; i++) {
        unBuffer.read(inFile);
        unBuffer.unpack(&otroTestStruct);
        if(!this->assertEquals(unTestStruct[i], otroTestStruct)) {cerr<<"Las estructuras son diferentes"<<endl; return -1;};
    };
    inFile.close();
    
    remove("testVarBuffer.dat");
    cout<<"Prueba testVarBuffer EXITOSA"<<endl;
    return 0;
}
