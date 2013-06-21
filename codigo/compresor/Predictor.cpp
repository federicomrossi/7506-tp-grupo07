#include "Predictor.h"
#include "ListaExclusion.h"
#include "compresion_Aritmetico.h"
#include "Contexto.h"
#include "CtxM1.h"
#include "Ctx0.h"
#include "CtxN.h"

#include <iterator>

Predictor::Predictor(unsigned short orden, std::string archivoDest){
    this->listaExclusion= new ListaExclusion();
    this->aritmetico = new Aritmetico(archivoDest);
    this->orden = orden;
    listaContextos = new list<Contexto*>;
    Contexto* c = new CtxM1();
    listaContextos->push_front(c);
    if(orden > -1){
        listaContextos->push_front(new Ctx0);
        if(orden > 0){
            for(int i=0;i<orden;i++){
                listaContextos->push_front(new CtxN(i+1));
            }
        }
    }
}

Predictor::~Predictor(){
    std::list<Contexto*>::iterator it;
    for(it = listaContextos->begin();it != listaContextos->end();it++){
        delete *it;
    }
    delete listaContextos;
    delete aritmetico;
}

int Predictor::comprimir(char c,std::string contextoActual){
    std::list<Contexto*>::iterator it;
    probabilidades probas;
    for(it = listaContextos->begin();it != listaContextos->end();it++){
        probas = (*it)->getProbabilidades(c, contextoActual,*listaExclusion);
        (*it)->aumentarFrec(c,contextoActual);
        if(probas.probaCaracter > 0){
            aritmetico->comprimir(probas.probaCaracter,probas.probaAcumulada,probas.probaTotal+probas.cantDistintos);
            listaExclusion->reset();
            break;
        }else{
            aritmetico->comprimir(probas.cantDistintos,probas.probaTotal,probas.probaTotal+probas.cantDistintos);
        }
    }
    return 0;
}

int Predictor::finalizarCompresion(std::string contextoActual){
    std::list<Contexto*>::iterator it;
    probabilidades probas;
    for(it = listaContextos->begin();it != listaContextos->end();it++){
        probas = (*it)->getProbabilidadesEscape(contextoActual,*listaExclusion);
        if((distance(it,listaContextos->end())) == 1){
            aritmetico->comprimir(1,probas.probaTotal,probas.probaTotal+1);
        }else{
            aritmetico->comprimir(probas.cantDistintos,probas.probaTotal,probas.probaTotal+probas.cantDistintos);
        }
    }
    aritmetico->finalizarCompresion();
    return 0;
}

int Predictor::inicializarDescompresion(){
    aritmetico->inicializarDescompresion();
    return 0;
}

int Predictor::descomprimir(std::string contextoActual){
    std::list<Contexto*>::iterator it;
    unsigned short int probaAcumulada = 0;
    int caracter = -1;
    unsigned short total=0;
    for(it = listaContextos->begin();it != listaContextos->end();it++){
        //total LLAMAR A GET TOTAL DEL CONTEXTO
        probaAcumulada = aritmetico->descomprimir(total);
        caracter = (*it)->extraerCaracter(probaAcumulada,contextoActual,*listaExclusion);
        if(caracter > -1){
            (*it)->aumentarFrec(caracter, contextoActual);
            listaExclusion->reset();
            break;
        }
    }
    return caracter;
}
