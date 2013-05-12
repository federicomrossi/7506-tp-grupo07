//
//  main.cpp
//  FileHandler
//
//  Created by Federico Colangelo on 21/04/13.
//  Copyright (c) 2013 Federico Colangelo. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "Alumno.h"
#include "fisica_VarBuffer.h"

#define TESTCASES 10
#define BUFFSIZE 128

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
    ofstream outFile("testVarBuffer.dat",ios::out|ios::binary);
    
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
    
    ifstream inFile("testVarBuffer.dat",ios::in|ios::binary); 
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



/*
 ofstream file("nueva.dat",ios::out|ios::binary);
 Alumno nuevoAlumno = Alumno(89869,"sdfdsfds","Federico","Colangelo","Informatica");
 nuevoAlumno.print();
 Alumno otroAlumno = Alumno(5435,"Rodi","Rodri","Burdet","Electronica");
 Alumno recuFede = Alumno(43,"sfdsfdsf","fsdfdsfdsfdsfdsafd","fsdfdsfdsfdsf","sfdsfdsf");
 Alumno recuOtro = Alumno(543,"fdsfdsf","fsdfdsfds","fdsafdasfdsf","sdfdsfdsf");
 otroAlumno.print();
 recuFede.print();
 recuOtro.print();
 
 
 VarBuffer unBuffer = VarBuffer(64);
 //VarBuffer otroBuffer = VarBuffer(64);
 unBuffer.pack(&nuevoAlumno,sizeof(nuevoAlumno));
 unBuffer.write(file);
 unBuffer.pack(&otroAlumno,sizeof(otroAlumno));
 unBuffer.write(file);
 file.close();
 ifstream file2("nueva.dat",ios::in|ios::binary);
 unBuffer.read(file2);
 unBuffer.unpack(&recuFede);
 unBuffer.read(file2);
 unBuffer.unpack(&recuOtro);
 recuFede.print();
 recuOtro.print();
 file2.close();
 
 
 
 
 int size = sizeof(nuevoAlumno);
 char* buffer[10];
 memcpy(&buffer,&nuevoAlumno,size);
 
 file.write((char*)&buffer[0], size);
 file.close();
 
 char* buffer2[10];
 ifstream file2("nueva.dat",ios::in|ios::binary);
 file2.read((char*)&buffer2[0], size);
 
 
 memcpy(&otroAlumno, &buffer2, size);
 otroAlumno.print();
 file2.close();
 */
