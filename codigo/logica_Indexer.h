#ifndef INDEXER_H_INCLUDED
#define INDEXER_H_INCLUDED

#include <iostream>

class Indexer{
    public:
        Indexer();
        ~Indexer();
        int indexarCancionesDesde(std::string path, int mode); //0 scratch ; 1 append
        int eliminarTodo();
    private:
        int estaIndexado(std::string);
};



#endif // INDEXER_H_INCLUDED
