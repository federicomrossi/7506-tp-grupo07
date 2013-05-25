#ifndef LOGICA_RTTGENERATOR_H_INCLUDED
#define LOGICA_RTTGENERATOR_H_INCLUDED

#include "logica_ArbolBmas.h"
#include "domain_RTTocurrencia.h"
#include "domain_RTTreferencia.h"
#include <list>

class RTTgenerator{
    public:
        RTTgenerator(std::string path);
        ~RTTgenerator();
        int indexarPalabra(std::string palabra, unsigned int song, unsigned int position);
        int pack();
        int eliminarTodo();
        int recuperar(std::string frase, std::list<unsigned int> *lista);
    private:
        int esIndexable(std::string palabra);
        unsigned int obtenerId(std::string palabra);
        int guardarOcurrencia(RTTocurrencia* ocur);
        int printOcurrencias();
        unsigned int getRefListaDocs();
        unsigned int getRefListaPos();
        int guardarListaPos(std::list<unsigned int>* lista);
        int guardarListaDocs(std::list<RTTreferencia*>* lista);
        ArbolBmas<RTTreferencia> *arbol;
        std::string temporalOcurrencias;
        std::string nonIndexableWords;
        std::string listasInvertidasDocumentos;
        std::string listasInvertidasPosiciones;
        std::string palabras;
        std::string arbolName;
};


#endif // LOGICA_RTTGENERATOR_H_INCLUDED
