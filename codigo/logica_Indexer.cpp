#include <iostream>
#include "fisica_DirHandler.h"
#include "logica_Indexer.h"
#include "logica_FileHandler.h"
#include "logica_Validator.h"
#include "logica_IndicePrimario.h"
#include "logica_Utils.h"

Indexer::Indexer(){
}

Indexer::~Indexer(){
}

int Indexer::eliminarTodo(){
    return 0;
}

int Indexer::indexarCancionesDesde(std::string path, int mode){
    DirHandler *dirH = new DirHandler(path.c_str());
    FileHandler *fileH = new FileHandler();
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
                std::list<std::string>* autores = new std::list<std::string>;
                Utils::getAutoresFromHeader(header,autores);
                delete autores;
                std::string titulo = Utils::getTituloFromHeader(header);
                std::cout << "TITULO: " << titulo << endl;
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
    s = Utils::getClaveFromHeader(header);
    std::cout << s << endl;
    if(ind->recuperar(s)){
        return 1;
    }
    return 0;
}
