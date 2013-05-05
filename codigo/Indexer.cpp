#include <iostream>
#include "Indexer.h"
#include "dirHandler.h"

Indexer::Indexer(){
}

Indexer::~Indexer(){
}

int Indexer::eliminarTodo(){
    return 0;
}

int Indexer::indexarCancionesDesde(std::string path, int mode){
    dirHandler *dirH = new dirHandler(path.c_str());
    dirH->getFiles(path.c_str());
    std::list<string> *archivos = dirH->getFileList();
    std::list<string>::iterator it;
    for(it = archivos->begin(); it != archivos->end(); it++){

    }
    if(mode){
        //COSAS DE APPEND
    }
    return 0;
}
