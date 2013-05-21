#include "logica_IndiceTitulo.h"
#include "domain_AutorId.h"
#include "logica_SortExterno.h"
#include <fstream>
#include <string.h>

IndiceTitulo::IndiceTitulo(std::string path){
    this->temporalOcurrencias = path + ".ocurrenciasTitulo";
    this->titulos = path + ".titulos";
}

IndiceTitulo::IndiceTitulo(){
}

IndiceTitulo::~IndiceTitulo(){
}


int IndiceTitulo::agregar(unsigned int songPosition, std::string titulo){
    unsigned int tituloId = this->obtenerId(titulo);
    AutorOcurrencia* ocur = new AutorOcurrencia(tituloId, songPosition);
    this->guardarOcurrencia(ocur);
    delete ocur;
    return 0;
}

unsigned int IndiceTitulo::obtenerId(std::string titulo){
    std::ifstream file;
    std::string p;
    int found = 0;
    unsigned int id =0;
    file.open(this->titulos.c_str(), std::fstream::in | std::fstream::out);
    AutorId* aui = new AutorId();
    if(file.good()){
        file >> *aui;
        while(!file.eof() && !found){
            id = aui->getId();
            const char* c=aui->getAutor();
            if(!strcmp(c,titulo.c_str())){
                found=1;
            }
            file >> *aui;
        }
    }
    file.close();
    delete aui;
    if(!found){
        std::ofstream file2(titulos.c_str(), std::fstream::app);
        id = file2.tellp();
        AutorId* aid = new AutorId(titulo.c_str(),id);
        file2 << *aid;
        file2.close();
    }
    return id;
}

int IndiceTitulo::guardarOcurrencia(AutorOcurrencia* ocur){
    std::ofstream file;
    file.open(temporalOcurrencias.c_str(),std::fstream::app);
    file << *ocur;
    file.close();
    return 0;
}

int IndiceTitulo::pack(){
    SortExterno<AutorOcurrencia>* sort = new SortExterno<AutorOcurrencia>(this->temporalOcurrencias,4096);
    this->printOcurrencias();
    std::cout << "ORDENANDO" << std::endl;
    sort->ordenar();
    this->printOcurrencias();
    return  0;
}

int IndiceTitulo::printOcurrencias(){
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

int IndiceTitulo::recuperar(std::string titulo, unsigned int* songRef){
    *songRef = 0;
    return 0;
}

int IndiceTitulo::eliminarTodo(){
    return 0;
}
