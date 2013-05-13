#ifndef INDICETITULO_H_INCLUDED
#define INDICETITULO_H_INCLUDED

#include <iostream>

class IndiceTitulo{
    public:
        IndiceTitulo();
        ~IndiceTitulo();
        int agregar(int posArch, std::string titulo);
        int recuperar(std::string titulo, int **posArch);
        int eliminarTodo();
    private:
        //UN ARBOL


};

#endif // INDICETITULO_H_INCLUDED
