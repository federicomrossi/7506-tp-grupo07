#ifndef INDICETITULO_H_INCLUDED
#define INDICETITULO_H_INCLUDED

#include <iostream>
#include "domain_AutorOcurrencia.h"

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
        //UN HASH

        std::string temporalOcurrencias;
        std::string titulos;

};

#endif // INDICETITULO_H_INCLUDED
