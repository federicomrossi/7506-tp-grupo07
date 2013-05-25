#include "logica_IndiceTitulo.h"
#include "domain_AutorId.h"
#include "logica_SortExterno.h"
#include "domain_TituloReferencias.h"
#include <fstream>
#include <string.h>
#include <climits>

IndiceTitulo::IndiceTitulo(std::string path){
    this->temporalOcurrencias = path + ".ocurrenciasTitulo";
    this->titulos = path + ".titulos";
    this->listaRefs = path + ".titulosRef";
    //this->hash = new BlockTable<
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
        delete aid;
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
    sort->ordenar();
    delete sort;
    std::ifstream file;
    file.open(this->temporalOcurrencias.c_str());
    AutorOcurrencia aid;
    unsigned int titulo;
    unsigned int cant = 0;
    unsigned int refLista;
    std::list<unsigned int>* lista;
    file >> aid;
    while(!file.eof()){
        titulo = aid.getAutorId();
        cant = 0;
        TituloReferencias* ar = new TituloReferencias(titulo);
        refLista = this->getRefLista();
        lista = new std::list<unsigned int>();
        while((aid.getAutorId() == titulo) && !file.eof()){
            switch(cant){
                case 0: ar->setRef1(aid.getDocumentoId());
                        break;
                case 1:
                        ar->setRef2(aid.getDocumentoId());
                        break;
                case 2:
                        ar->setRef3(aid.getDocumentoId());
                        break;
                case 3: ar->setRefLista(refLista);
                default: lista->push_back(aid.getDocumentoId());
            }
            cant++;
            file >> aid;
        }
        ar->setCant(cant);
        if(cant > 3){
            this->guardarRefLista(lista);
        }else{
            ar->setRefLista(UINT_MAX);
        }
        //aborl->guardar(ar);
        delete ar;
        delete lista;
    }
    remove(this->temporalOcurrencias.c_str());
    return  0;
}

unsigned int IndiceTitulo::getRefLista(){
    std::ofstream file;
    file.open(this->listaRefs.c_str(),std::fstream::app);
    unsigned int pos = file.tellp();
    file.close();
    return pos;
}

int IndiceTitulo::guardarRefLista(std::list<unsigned int>* lista){
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

int IndiceTitulo::recuperar(std::string titulo, std::list<unsigned int> *lista){
 /*   unsigned int clave = this->obtenerId(titulo);
//    hash->abrir(this->hashName.c_str());
    TituloReferencias* ar = new TituloReferencias();
    bool b = hash->buscar(clave, *ar);
    if(b){
        unsigned int* refs = ar->getRefs();
        unsigned int stop = ar->getCant() > 3 ? 3: ar->getCant();
        for(unsigned int i=0;i<stop;i++){
            lista->push_back(refs[i]);
        }
        if(ar->getCant() > 3){
            std::ifstream file;
            file.open(this->listaRefs.c_str());
            file.seekg(ar->getRefLista());
            unsigned int cant;
            file.read((char*)&cant,sizeof(unsigned int));
            for(unsigned int i=0;i < cant;i++){
                unsigned int ref;
                file.read((char*)&ref,sizeof(unsigned int));
                lista->push_back(ref);
            }
            file.close();
        }
    }
    arbol->cerrar();*/
    return 0;
}

int IndiceTitulo::eliminarTodo(){
    remove(listaRefs.c_str());
    remove(titulos.c_str());
    return 0;
}
