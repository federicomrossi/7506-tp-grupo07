#ifndef INDICEAUTOR_H_INCLUDED
#define INDICEAUTOR_H_INCLUDED

#include <iostream>
#include "domain_AutorOcurrencia.h"

class IndiceAutor{
    public:
        IndiceAutor(std::string path);
        ~IndiceAutor();
        int agregar(unsigned int posArch, std::string autor);
        int recuperar(std::string autor, unsigned int* posArch);
        int eliminarTodo();
        int pack();
    private:
        unsigned int obtenerId(std::string palabra);
        int guardarOcurrencia(AutorOcurrencia* ocur);
        int printOcurrencias();


        //UN ARBOL
        std::string temporalOcurrencias;
        std::string autores;


};



#endif // INDICEAUTOR_H_INCLUDED
