#include <iostream>
#include "Indexer.h"
#include "dirHandler.h"
#include "fileHandler.h"
#include "Validator.h"
#include "IndicePrimario.h"
#include "Utils.h"

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
        std::string header = fileH->getFirstLine(*it);
        cout << "Validando Header.. " << header << endl;
        int size;
        if(!(size = Validator::validateHeader(header))){
            std::cout << "Error en header. Descartado." << endl;
        }else{
            std::cout << "Header OK." << endl << "Verificando si ya esta indexada..";
            if (this->estaIndexado(header)){
                std::cout << "Archivo ya indexado. Descartado" << endl;
            }else{
                std::cout << "OK." << endl << "Indexando..";

            }
        }
    }
    if(mode){
        //COSAS DE APPEND
    }
    delete dirH;
    return 0;
}


int Indexer::estaIndexado(std::string header){
    IndicePrimario *ind = new IndicePrimario;
    std::string s;
    Utils::getClaveFromHeader(header, &s);
    std::cout << s << endl;
    if(ind->recuperar(s)){
        return 1;
    }
    return 0;
}
