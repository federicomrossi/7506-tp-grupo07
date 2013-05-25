#include "logica_IndiceAutor.h"
#include "logica_SortExterno.h"
#include "domain_AutorId.h"
#include "domain_AutorReferencias.h"
#include <string.h>
#include <string>
#include <fstream>
#include <iostream>
#include <climits>

IndiceAutor::IndiceAutor(std::string path){
    this->temporalOcurrencias = path + ".ocurrenciasAutor";
    this->autores = path + ".autores";
    this->listaRefs = path + ".autoresRef";
    this->arbolName = path + ".arbolAutores";
    this->arbol = new ArbolBmas<AutorReferencias>();

}

IndiceAutor::~IndiceAutor(){
    arbol->cerrar();
    delete arbol;
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
    sort->ordenar();
    delete sort;
    std::ifstream file;
    file.open(this->temporalOcurrencias.c_str());
    AutorOcurrencia aid;
    unsigned int autor;
    unsigned int cant = 0;
    unsigned int refLista;
    std::list<unsigned int>* lista;
    arbol->abrir(this->arbolName.c_str());
    file >> aid;
    while(!file.eof()){
        autor = aid.getAutorId();
        cant = 0;
        AutorReferencias* ar = new AutorReferencias(autor);
        refLista = this->getRefLista();
        lista = new std::list<unsigned int>();
        while((aid.getAutorId() == autor) && !file.eof()){
            switch(cant){
                case 0: ar->setRef1(aid.getDocumentoId());
                        break;
                case 1:
                        ar->setRef2(aid.getDocumentoId());
                        break;
                case 2:
                        ar->setRef3(aid.getDocumentoId());
                        break;
                case 3:
                        ar->setRef4(aid.getDocumentoId());
                        break;
                case 4:
                        ar->setRef5(aid.getDocumentoId());
                        break;
                case 5: ar->setRefLista(refLista);
                default: lista->push_back(aid.getDocumentoId());
            }
            cant++;
            file >> aid;
        }
        ar->setCant(cant);
        if(cant > 5){
            this->guardarRefLista(lista);
        }else{
            ar->setRefLista(UINT_MAX);
        }
        arbol->insertar(ar->getClave(),*ar);
        delete ar;
        delete lista;
    }
    arbol->imprimir();
    arbol->cerrar();
    return  0;
}

unsigned int IndiceAutor::getRefLista(){
    std::ofstream file;
    file.open(this->listaRefs.c_str(),std::fstream::app);
    unsigned int pos = file.tellp();
    file.close();
    return pos;
}

int IndiceAutor::guardarRefLista(std::list<unsigned int>* lista){
    unsigned int cant = lista->size();
    std::ofstream file;
    file.open(this->listaRefs.c_str(),std::fstream::app);
    file.write((char*)&cant,sizeof(cant));
    for(std::list<unsigned int>::iterator it = lista->begin();it != lista->end();it++){
        file.write((char*)&*it,sizeof(unsigned int));
    }
    file.close();
    return 0;
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
