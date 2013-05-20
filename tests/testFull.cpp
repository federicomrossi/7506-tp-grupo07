//
//  main.cpp
//  FileHandler
//
//  Created by Federico Colangelo on 21/04/13.
//  Copyright (c) 2013 Federico Colangelo. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "TestArchivoBloques.h"
#include "TestVarBuffer.h"

int main(int argc, const char * argv[])
{
    TestArchivoBloques testArchivoBloques = TestArchivoBloques();
    TestVarBuffer testVarBuffer = TestVarBuffer();
    
    testVarBuffer.test();
    testArchivoBloques.test();
    
    
    return 0;
}
