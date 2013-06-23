#include "compresion_Aritmetico.h"
#include <fstream>

/**
* Autor: Pablo Rodriguez
* Testea el aritmetico de forma estatica. Debe existir el archiv 'aComprimir' el cual sera comprimido.
* El resultado comprimido sera almacenado en el archivo 'destinoComprimido'
* El resultado descomprimido sera almacenado en el archivo 'destinoDescomprimido'
*/

int testAritmetico(){
    FILE * f;
    remove("logCompresor.txt");
    remove("logDescompresor.txt");
    remove("destinoComprimido");
    remove("destinoDescomprimido");
    remove("logTabla.txt");
    f=fopen("logCompresor.txt","a");
    std::ifstream source;
    source.open("aComprimir");
    unsigned short tabla[257];
    for(int i = 0; i< 257;i++){
        tabla[i] =0;
    }
    unsigned char c;
    unsigned short total=0;
    source.read((char*)&c,sizeof(char));
    while(!source.eof()){
        (*(tabla+c))++;
        source.read((char*)&c,sizeof(char));
        total++;
    }
    tabla[256] = 1;
    total++;
    Aritmetico* arit = new Aritmetico("destinoComprimido");
    source.close();
    source.open("aComprimir");
    source.read((char*)&c,sizeof(char));
    while(!source.eof()){
        unsigned short probaAcumulada=0;
        for(int i=0;i<c;i++){
            probaAcumulada += tabla[i];
        }
        fprintf(f,"Comprimo %c \n",c);
        fflush(f);
        arit->comprimir(*(tabla+c),probaAcumulada,total);
        source.read((char*)&c,sizeof(char));
    }
    arit->comprimir(1,total-1,total);
    arit->finalizarCompresion();
    source.close();
    fclose(f);
    f=fopen("logTabla.txt","w");
    delete arit;
    arit = new Aritmetico("destinoComprimido");
    arit->inicializarDescompresion();
    std::ofstream fileDest;
    fileDest.open("destinoDescomprimido",std::fstream::app);
    int parcial=0;
    for(int j=0;j<256;j++){
        fprintf(f,"Caracter %c    %d     %d  \n",j,tabla[j],parcial);
        parcial += tabla[j];
    }
    fclose(f);
    f=fopen("logDescompresor.txt","a");
    unsigned short probaAcumulada = 0;
    int finished =0;
    while(!finished){
        probaAcumulada = arit->descomprimir(total);
        unsigned short acumuladaCalculada = 0;
        int i;
        for(i =0;i<257;i++){
            if(probaAcumulada < acumuladaCalculada){
                break;
            }
            acumuladaCalculada += tabla[i];
        }
        if(i<257){
            char caracter = (char)(i-1);
            fprintf(f,"Proba Acumulada %d \n",probaAcumulada);
            fprintf(f,"DesComprimo %c \n",caracter);
            fflush(f);
            fileDest.write(&caracter,sizeof(caracter));
            arit->actualizarRangosDescompresion(tabla[i-1],acumuladaCalculada - tabla[i-1], total);
        }else{
            finished = 1;
        }
    }
    fclose(f);
    fileDest.close();
    return 0;
}
