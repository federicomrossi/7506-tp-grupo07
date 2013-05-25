#ifndef INDICETITULO_H_INCLUDED
#define INDICETITULO_H_INCLUDED

#include <iostream>
#include "domain_AutorOcurrencia.h"
#include <list>

class IndiceTitulo{
    public:
        IndiceTitulo(std::string path);
        IndiceTitulo();
        ~IndiceTitulo();
        int agregar(unsigned int posArch, std::string titulo);
        int recuperar(std::string titulo, unsigned int* posArch);
        int eliminarTodo();
        int pack();
    private:
        unsigned int obtenerId(std::string palabra);
        int guardarOcurrencia(AutorOcurrencia* ocur);
        int printOcurrencias();
        unsigned int getRefLista();
        int guardarRefLista(std::list<unsigned int>* lista);
        //UN HASH

        std::string temporalOcurrencias;
        std::string titulos;
        std::string listaRefs;

};

#endif // INDICETITULO_H_INCLUDED
