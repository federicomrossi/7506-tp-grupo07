#include "Predictor.h"
#include "ListaExclusion.h"
#include "compresion_Aritmetico.h"
#include "Contexto.h"
#include "CtxM1.h"
#include "Ctx0.h"
#include "CtxN.h"
#include <stdio.h>

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
    FILE *f;
    f=fopen("logPPMC.txt","a");
    std::list<Contexto*>::iterator it;
    probabilidades probas;
    fprintf(f,"Letra: %c \n",c);
    for(it = listaContextos->begin();it != listaContextos->end();it++){
        probas = (*it)->getProbabilidades(c, contextoActual,listaExclusion);
        fprintf(f,"Probabilidad caracter: %d \n",probas.probaCaracter);
        fprintf(f,"Probabilidad acumulada: %d \n",probas.probaAcumulada);
        fprintf(f,"Probabilidad total: %d \n",probas.probaTotal);
        (*it)->aumentarFrec(c,contextoActual);
        if(probas.probaCaracter > 0){
            if((distance(it,listaContextos->end())) == 1){
                fprintf(f,"Comprimo Caracter Probabilidad %d/%d \n",probas.probaCaracter,probas.probaTotal);
                aritmetico->comprimir(probas.probaCaracter,probas.probaAcumulada,probas.probaTotal);
            }else{
                fprintf(f,"Comprimo Caracter Probabilidad %d/%d \n",probas.probaCaracter,probas.probaTotal+probas.cantDistintos);
                aritmetico->comprimir(probas.probaCaracter,probas.probaAcumulada,probas.probaTotal+probas.cantDistintos);
            }listaExclusion->reset();
            break;
        }else{
            fprintf(f,"Comprimo Escape Probabilidad %d/%d \n",probas.cantDistintos,probas.probaTotal+probas.cantDistintos);
            aritmetico->comprimir(probas.cantDistintos,probas.probaTotal,probas.probaTotal+probas.cantDistintos);
        }
    }
    fclose(f);
    return 0;
}

int Predictor::finalizarCompresion(std::string contextoActual){
    std::list<Contexto*>::iterator it;
    probabilidades probas;
    for(it = listaContextos->begin();it != listaContextos->end();it++){
        probas = (*it)->getProbabilidadesEscape(contextoActual,listaExclusion);
        if((distance(it,listaContextos->end())) == 1){
            aritmetico->comprimir(1,probas.probaTotal-1,probas.probaTotal);
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
    probabilidades probas;
    for(it = listaContextos->begin();it != listaContextos->end();it++){
        probas = (*it)->getProbabilidadesEscape(contextoActual,listaExclusion);
        if(probas.probaTotal+probas.cantDistintos == 0){
            caracter = -1;
            break;
        }else{
            probaAcumulada = aritmetico->descomprimir(probas.probaTotal+probas.cantDistintos);
            caracter = (*it)->extraerCaracter(probaAcumulada,contextoActual,listaExclusion);
        }
        if(caracter > -1){
            probas = (*it)->getProbabilidades((char)caracter,contextoActual,listaExclusion);
            aritmetico->actualizarRangosDescompresion(probas.probaCaracter,probas.probaAcumulada,probas.probaTotal+probas.cantDistintos);
            (*it)->aumentarFrec(caracter,contextoActual);
            while(it != listaContextos->begin()){
                it--;
                (*it)->aumentarFrec(caracter, contextoActual);
            }
            listaExclusion->reset();
            break;
        }else{
            probas = (*it)->getProbabilidadesEscape(contextoActual,listaExclusion);
            aritmetico->actualizarRangosDescompresion(probas.cantDistintos,probas.probaTotal,probas.probaTotal+probas.cantDistintos);
        }
    }
    return caracter;
}
