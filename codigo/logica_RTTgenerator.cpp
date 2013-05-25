#include <string>
#include <fstream>
#include "logica_RTTgenerator.h"
#include "domain_RTTocurrencia.h"
#include <string.h>
#include "logica_SortExterno.h"



RTTgenerator::RTTgenerator(std::string path){
    //this->arbol = new ArbolBmas();
    this->temporalOcurrencias=path+".ocurrencias";
    this->palabras=path+".palabras";
    this->nonIndexableWords=path+ ".palabrasNoIndexables";
    this->listasInvertidasDocumentos=path+ ".listaDocumentos";
    this->listasInvertidasPosiciones=path+ ".listaPosiciones";
    this->arbolName = path + ".arbolRTT";
    this->arbol = new ArbolBmas<RTTreferencia>();
}

RTTgenerator::~RTTgenerator(){
    arbol->cerrar();
    delete arbol;
}

int RTTgenerator::indexarPalabra(std::string palabra, unsigned int song, unsigned int position){
    if(esIndexable(palabra)){
        unsigned int idPalabra = this->obtenerId(palabra);
        RTTocurrencia ocurrencia(idPalabra, song, position);
        this->guardarOcurrencia(&ocurrencia);
    }
    return 0;
}

int RTTgenerator::esIndexable(std::string){
    return 1;
}

unsigned int RTTgenerator::obtenerId(std::string palabra){
    std::fstream file;
    std::string p;
    int found = 0;
    unsigned int id =0;
    file.open(palabras.c_str(), std::fstream::in | std::fstream::out);
    if(file.good()){
        while(!file.eof() && !found){
            id = file.tellg();
            getline(file,p);
            if(!p.compare(palabra)){
                found=1;
            }
        }
    }
    file.close();
    if(!found){
        std::ofstream file2(palabras.c_str(), std::fstream::app);
        file2 << palabra << endl;
        file2.close();
    }

    return id;
}

int RTTgenerator::guardarOcurrencia(RTTocurrencia* ocur){
    std::ofstream file;
    file.open(temporalOcurrencias.c_str(),std::fstream::app);
    file << *ocur;
    file.close();
    return 0;
}


int RTTgenerator::pack(){
    SortExterno<RTTocurrencia>* sort = new SortExterno<RTTocurrencia>(this->temporalOcurrencias,4096);
    sort->ordenar();
    delete sort;
    std::ifstream file;
    file.open(this->temporalOcurrencias.c_str());
    RTTocurrencia ocur;
    unsigned int idPalabra;
    unsigned int idDoc;
    unsigned int cantDocs = 0;
    unsigned int cantPos = 0;
    unsigned int refListaDocs;
    unsigned int refListaPos;
    std::list<RTTreferencia*>* listaDocs;
    std::list<unsigned int>* listaPos;
    arbol->abrir(this->arbolName.c_str());
    file >> ocur;
    while(!file.eof()){
        idPalabra = ocur.getPalabraId();
        cantDocs = 0;
        RTTreferencia* ar = new RTTreferencia(idPalabra);
        refListaDocs = this->getRefListaDocs();
        ar->setRefLista(refListaDocs);
        listaDocs = new std::list<RTTreferencia*>();
        while((ocur.getPalabraId() == idPalabra) && !file.eof()){
            idDoc = ocur.getDocumentoId();
            cantPos = 0;
            refListaPos = this->getRefListaPos();
            RTTreferencia* refPos = new RTTreferencia(idDoc);
            refPos->setRefLista(refListaPos);
            listaPos = new std::list<unsigned int>;
            while((ocur.getDocumentoId() == idDoc) && !file.eof()){
                listaPos->push_back(ocur.getPosition());
                cantPos++;
                file >> ocur;
            }
            this->guardarListaPos(listaPos);
            delete listaPos;
            listaDocs->push_back(refPos);
            cantDocs++;
        }
        this->guardarListaDocs(listaDocs);
        arbol->insertar(ar->getClave(),*ar);
        delete ar;
        delete listaDocs;
    }
    arbol->imprimir();
    arbol->cerrar();
    return  0;
}

unsigned int RTTgenerator::getRefListaDocs(){
    std::ofstream file;
    file.open(this->listasInvertidasDocumentos.c_str(),std::fstream::app);
    unsigned int pos = file.tellp();
    file.close();
    return pos;
}


unsigned int RTTgenerator::getRefListaPos(){
    std::ofstream file;
    file.open(this->listasInvertidasPosiciones.c_str(),std::fstream::app);
    unsigned int pos = file.tellp();
    file.close();
    return pos;
}

int RTTgenerator::guardarListaDocs(std::list<RTTreferencia*> *lista){
    unsigned int cant = lista->size();
    std::ofstream file;
    file.open(this->listasInvertidasDocumentos.c_str(),std::fstream::app);
    file.write((char*)&cant,sizeof(cant));
    for(std::list<RTTreferencia*>::iterator it = lista->begin();it != lista->end();it++){
        unsigned int p = (*it)->getClave();
        file.write((char*)&p,sizeof(unsigned int));
        p = (*it)->getRefLista();
        file.write((char*)&p,sizeof(unsigned int));
        delete *it;
    }
    file.close();
    return 0;
}

int RTTgenerator::guardarListaPos(std::list<unsigned int> *lista){
    unsigned int cant = lista->size();
    std::ofstream file;
    file.open(this->listasInvertidasPosiciones.c_str(),std::fstream::app);
    file.write((char*)&cant,sizeof(cant));
    for(std::list<unsigned int>::iterator it = lista->begin();it != lista->end();it++){
        file.write((char*)&*it,sizeof(unsigned int));
    }
    file.close();
    return 0;
}

int RTTgenerator::printOcurrencias(){
    std::ifstream file;
    file.open(temporalOcurrencias.c_str(), std::fstream::binary);
    RTTocurrencia* o = new RTTocurrencia;
    file >> *o;
    while(!file.eof()){
        std::cout << "(" << o->getPalabraId() << "," << o->getDocumentoId() << "," << o->getPosition() << ")";
        file >> *o;
    }
    file.close();
    return 0;
}
