#include <iostream>
#include "Indexer.h"
#include "dirHandler.h"
#include "fileHandler.h"
#include "Validator.h"

Indexer::Indexer(){
}

Indexer::~Indexer(){
}

int Indexer::eliminarTodo(){
    return 0;
}

int Indexer::indexarCancionesDesde(std::string path, int mode){
    dirHandler *dirH = new dirHandler(path.c_str());
    fileHandler *fileH = new fileHandler();
    dirH->getFiles(path.c_str());
    std::list<string> *archivos = dirH->getFileList();
    std::list<string>::iterator it;
    for(it = archivos->begin(); it != archivos->end(); it++){
        cout << "Indexando archivo..  " << *it << endl;
        string header = fileH->getFirstLine(*it);
        cout << "Validando Header.. " << header << endl;
        int size;
        if(!(size = Validator::validateHeader(header))){
            std::cout << "Error en header. Descartado." << endl;
        }else{
            std::cout << "Header OK." << endl << "Verificando si ya esta indexada..";


        }
    }
    if(mode){
        //COSAS DE APPEND
    }
    delete dirH;
    return 0;
}
