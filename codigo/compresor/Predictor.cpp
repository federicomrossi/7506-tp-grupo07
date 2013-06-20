#include "Predictor.h"
#include <iterator>

Predictor::Predictor(unsigned short orden,std:string archivoDest){
    this->listaExclusion
    this->aritmetico = new Aritmetico(archivoDest);
    this->orden = orden;
    listaContextos = new list<Contexto*>;
    listaContextos->push_front(new CtxM1);
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
    for(it = listaContextos->begin();it != listaContextos->end();i++){
        delete *it;
    }
    delete listaContextos;
}

int Predictor::comprimir(char c,std::string contextoActual){
    std::list<Contexto*>::iterator it;
     probabilidades probas;
    for(it = listaContextos->begin();it != listaContextos->end();i++){
        probas = (*it)->getProbabilidades(c, contextoActual);
        (*it)->aumentarFrec(c,contextoActual);
        if(probas.probaCaracter > 0){
            aritmetico->comprimir(probas.probaCaracter,probas.probaAcumulada,probas.probaTotal+cantDistintos);
            break;
        }else{
            aritmetico->comprimir(probas.cantDistintos,probas.probaTotal,probas.probaTotal+probas.cantDistintos);
        }
    }
}

int Predictor::finalizarCompresion(std::string contextoActual){
    std::list<Contexto*>::iterator it;
    probabilidades probas;
    for(it = listaContextos->begin();it != listaContextos->end();i++){
        probas = (*it)->getProbabilidadesEscape(contextoActual);
        if((distance(it,listaContextos->end())) == 1){
            aritmetico->comprimir(1,probas.probaTotal,probas.probaTotal+1);
        }else{
            aritmetico->comprimir(probas.cantDistintos,probas.probaTotal,probas.probaTotal+probas.cantDistintos);
        }

    }
    aritmetico->finalizarCompresion();
}

int Predictor::inicializarDescompresion(){
    aritmetico->inicializarDescompresion();
}

int Predictor::descomprimir(std::string contextoActual){
    std::list<Contexto*>::iterator it;
    int probaAcumulada = 0;
    int caracter = -1;
    probabilidades probas;
    for(it = listaContextos->begin();it != listaContextos->end();i++){
        probaAcumulada =  aritmetico->descomprimir();
        caracter = (*it)->extraerCaracter(probaAcumulada);
        if(caracter > -1){
            (*it)->aumentarFrec(caracter, contextoActual);
            break;
        }
    }
    return caracter;
}
