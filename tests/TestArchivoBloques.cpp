//
//  TestArchivoBloques.cpp
//  Test2
//
//  Created by Federico Colangelo on 18/05/13.
//  Copyright (c) 2013 Federico Colangelo. All rights reserved.
//

#include "TestArchivoBloques.h"

TestArchivoBloques::TestArchivoBloques()
{
    
}

bool TestArchivoBloques::assertEquals(ArchivoBloquesTestStruct &unStruct, ArchivoBloquesTestStruct &otroStruct)
{
    return (unStruct.unEntero==otroStruct.unEntero && unStruct.unString==otroStruct.unString);
}

int TestArchivoBloques::test()
{
    ArchivoBloquesTestStruct testStruct1;
    testStruct1.unEntero=15;
    testStruct1.unString="fjlagjfldsgfd";
    
    ArchivoBloquesTestStruct testStruct2;
    testStruct2.unEntero=131;
    testStruct2.unString="fdasfdasfds";
    
    ArchivoBloquesTestStruct testStructTemp;
    
    //Pruebo la correcta creacion y apertura del archivo
    ArchivoBloques file(BLOCKSIZE,"testArchivoBloques.dat");
    file.crearArchivo();
    file.abrirArchivo();
    if (!file.estaAbierto()) {cerr<<"El archivo deberia estar abierto y esta cerrado"<<endl; return -1;};
    
    //Ahora pruebo que la escritura y lectura funcionen
    
    file.escribirBloque(&testStruct1, 2, sizeof(testStruct1));
    file.escribirBloque(&testStruct2, 7, sizeof(testStruct2));
    
    file.leerBloque(&testStructTemp, 2);
    if (!this->assertEquals(testStruct1, testStructTemp)) {cerr<<"Los struct no son iguales"<<endl; return -1;};
    file.leerBloque(&testStructTemp, 7);
    if (!this->assertEquals(testStruct2, testStructTemp)) {cerr<<"Los struct no son iguales"<<endl; return -1;};
    
    
    //Ahora pruebo que se borre correctamente
    file.borrarArchivo();
    file.abrirArchivo();
    testStruct1.unEntero=0;
    testStruct1.unString="";
    file.leerBloque(&testStruct1, 7);
    if (this->assertEquals(testStruct1, testStructTemp)) {cerr<<"Los struct son iguales"<<endl; return -1;};
    
    cout<<"Prueba testArchivosBloques EXITOSA"<<endl;
    return 0;

}