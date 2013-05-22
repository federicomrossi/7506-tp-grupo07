//
//  leerMain.cpp
//  Test2
//
//  Created by Federico Colangelo on 21/05/13.
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
    
    char a,d;
    int b,c;

    file.leerBloque(unSerBuff.getBuffer(),0 );
    unSerBuff.unpack(&a);
    unSerBuff.unpack(&b);
    //unSerBuff.unpack(&e);

    cout<<a<<endl;
    cout<<b<<endl;
    //cout<<a[2]<<endl;

    unSerBuff.clear();
    file.leerBloque(unSerBuff.getBuffer(), 1);
    unSerBuff.unpack(&c);
    unSerBuff.unpack(&d);
    unSerBuff.clear();
    cout<<c<<endl;
    cout<<d<<endl; 
    return 0;
}
