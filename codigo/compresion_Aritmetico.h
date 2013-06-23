#ifndef COMPRESION_ARITMETICO_H_INCLUDED
#define COMPRESION_ARITMETICO_H_INCLUDED
#include <string>

/**
* Autor: Pablo Rodriguez
* Compresor aritmetico. Precision 16 bits.
*
*/

class Aritmetico {
    public:
    Aritmetico(std::string fileDest);
    ~Aritmetico();
    int comprimir(unsigned short probaCaracter, unsigned short probaAcumulada, unsigned short total);
    unsigned short descomprimir(unsigned short total);
    int finalizarCompresion();
    int inicializarDescompresion();
    int actualizarRangosDescompresion(unsigned short probaCaracter, unsigned short probaAcumulada, unsigned short total);

    private:
    int checkBuffer();
    int readBufferDescompresion();
    std::string file;
    unsigned short piso;
    unsigned short techo;
    unsigned short UF;
    unsigned short codigoDescompresion;
    unsigned char bitBuffer;
    char bitCount;
    unsigned int posDescompresion;

};

#endif // COMPRESION_ARITMETICO_H_INCLUDED
