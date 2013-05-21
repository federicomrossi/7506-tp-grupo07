#include "logica_IndiceAutor.h"
#include "logica_SortExterno.h"
#include "domain_AutorId.h"
#include <string.h>
#include <string>
#include <fstream>
#include <iostream>


IndiceAutor::IndiceAutor(std::string path){
    this->temporalOcurrencias = path + ".ocurrenciasAutor";
    this->autores = path + ".autores";

}

IndiceAutor::~IndiceAutor(){
}


int IndiceAutor::agregar(unsigned int songPosition, std::string autor){
    unsigned int autorId = this->obtenerId(autor);
    AutorOcurrencia* ocur = new AutorOcurrencia(autorId, songPosition);
    this->guardarOcurrencia(ocur);
    delete ocur;
    return 0;
}

unsigned int IndiceAutor::obtenerId(std::string autor){
    std::ifstream file;
    std::string p;
    int found = 0;
    unsigned int id =0;
    file.open(this->autores.c_str(), std::fstream::in | std::fstream::out);
    AutorId* aui = new AutorId();
    if(file.good()){
        file >> *aui;
        while(!file.eof() && !found){
            id = aui->getId();
            const char* c=aui->getAutor();
            if(!strcmp(c,autor.c_str())){
                found=1;
            }
            file >> *aui;
        }
    }
    file.close();
    delete aui;
    if(!found){
        std::ofstream file2(autores.c_str(), std::fstream::app);
        id = file2.tellp();
        AutorId* aid = new AutorId(autor.c_str(),id);
        file2 << *aid;
        file2.close();
    }
    return id;
}

int IndiceAutor::guardarOcurrencia(AutorOcurrencia* ocur){
    std::ofstream file;
    file.open(temporalOcurrencias.c_str(),std::fstream::app);
    file << *ocur;
    file.close();
    return 0;
}

int IndiceAutor::pack(){
    SortExterno<AutorOcurrencia>* sort = new SortExterno<AutorOcurrencia>(this->temporalOcurrencias,4096);
    this->printOcurrencias();
    std::cout << "ORDENANDO" << std::endl;
    sort->ordenar();
    this->printOcurrencias();
    return  0;
}

int IndiceAutor::printOcurrencias(){
    std::ifstream file;
    file.open(temporalOcurrencias.c_str(), std::fstream::binary);
    AutorOcurrencia* o = new AutorOcurrencia();
    file >> *o;
    while(!file.eof()){
        std::cout << "(" << o->getAutorId() << "," << o->getDocumentoId() << ")";
        file >> *o;
    }
    file.close();
    return 0;
}


int IndiceAutor::recuperar(std::string autor, unsigned int* songRef){
    *songRef = 0;
    return 0;
}

int IndiceAutor::eliminarTodo(){
    return 0;
}
