#include <iostream>
#include <fstream>
#include <sstream>
#include "logica_Indexer.h"
#include "fisica_DirHandler.h"
#include "logica_FileHandler.h"
#include "logica_Validator.h"
#include "logica_Utils.h"

Indexer::Indexer(){
    fromPath=SOURCE_PATH;
    destPath=DEST_PATH;
    masterName = destPath+".master";
    rtt = new RTTgenerator(destPath);
    autores = new IndiceAutor(destPath);
    titulos =  new IndiceTitulo(destPath);
}

Indexer::~Indexer(){
    delete rtt;
    delete autores;
    delete titulos;
}

int Indexer::eliminarTodo(){
    remove(masterName.c_str());
    autores->eliminarTodo();
    titulos->eliminarTodo();
    rtt->eliminarTodo();
    return 0;
}

int Indexer::indexarCancionesDesde(int mode){
    DirHandler *dirH = new DirHandler(fromPath.c_str());
    FileHandler *fileH = new FileHandler();
    dirH->getFiles(fromPath.c_str());
    std::list<string> *archivos = dirH->getFileList();
    std::list<string>::iterator it;
    for(it = archivos->begin(); it != archivos->end(); it++){
        cout << "Indexando archivo..  " << *it << endl;
        std::string header = fileH->getFirstLine(*it);
        cout << "Validando Header.. " << header << endl;
        int size;
        if(!(size = Validator::validateHeader(header))){
            std::cout << "Error en header. Descartado." << std::endl;
        }else{
            std::cout << "Header OK." << std::endl << "Verificando si ya esta indexada..";
            if (this->estaIndexado(header)){
                std::cout << "Archivo ya indexado. Descartado" << endl;
            }else{
                std::cout << "OK." << std::endl;
                unsigned int songPosition = this->copyToMaster(*it, masterName);
                this->indexarAutores(header,songPosition);
                this->indexarTitulo(header,songPosition);
                this->generateRTT(*it,songPosition);
            }
        }
    }
    if(mode){
        autores->packAppend();
        titulos->packAppend();
        rtt->packAppend();
    }else{
        autores->pack();
        titulos->pack();
        rtt->pack();
    }


    delete dirH;
    delete fileH;
    return 0;
}


int Indexer::estaIndexado(std::string header){
    std::string s;
    std::string clave;
    s = Utils::getTituloFromHeader(header);
    clave = Utils::getClaveFromHeader(header);
    std::list<unsigned  int> refs;
    titulos->recuperarPlus(s,&refs);
    std::list<unsigned int>::iterator it;
    std::ifstream master;
    std::string header2;
    std::string clave2;
    for(it = refs.begin();it != refs.end();it++){
        master.open(this->masterName.c_str());
        master.seekg(*it);
        unsigned int size;
        master.read((char*) &size,sizeof(unsigned int));
        getline(master,header2);
        clave2 = Utils::getClaveFromHeader(header2);
        master.close();
        if(!clave.compare(clave2)){
            return 1;
        }
    }
    return 0;
}

int Indexer::copyToMaster(std::string from, std::string to){
    std::ifstream source(from.c_str());
    std::ofstream dest(to.c_str(), std::fstream::app);
    unsigned int pos = dest.tellp();
    source.seekg(0,std::ios_base::end);
    unsigned int tam = source.tellg();
    source.seekg(0,std::ios_base::beg);
    dest.write((char*)&tam, sizeof(tam));
    //dest << tam;
    dest << source.rdbuf();
    source.close();
    dest.close();
    return pos;
}

int Indexer::indexarAutores(std::string header, unsigned int songPosition){
    std::list<std::string>* autoresLista = new std::list<std::string>;
    Utils::getAutoresFromHeader(header,autoresLista);
    std::list<std::string>::iterator it;
    for(it = autoresLista->begin(); it != autoresLista->end();it++){
        this->autores->agregar(songPosition,*it);
    }
    delete autoresLista;
    return 0;
}

int Indexer::indexarTitulo(std::string header, unsigned int songPosition){
    std::string titulo = Utils::getTituloFromHeader(header);
    titulos->agregar(songPosition,titulo);
    return 0;
}

int Indexer::generateRTT(std::string songPath, unsigned int songPosition){
    std::ifstream f;
    std::string palabra;
    std::string linea;
    unsigned int position = 0;
    f.open(songPath.c_str());
    getline(f,linea); //descarto el header
    while(getline(f,linea)){
        std::istringstream lineaS(linea);
        while(getline(lineaS,palabra,' ')){
            palabra = Utils::uniformizarString(palabra);
            rtt->indexarPalabra(palabra, songPosition,position);
            position++;
        }
    }
    f.close();
    return 0;
}



