#include "PPMC.h"
#include <fstream>

PPMC::PPMC(int orden,std::string archivo){
    predictor = new Predictor(orden,archivo+".ppmc");

}

PPMC::~PPMC(){
    delete predictor;
}

int PPMC::comprimir(string archivoSource){
    ifstream file;
    file.open(archivoSource.c_str());
    if(!file.good()){
        printf("No se pudo abrir el archivo de origen");
    }
    char caracter;
    string contextoActual;
    file.read(&caracter,sizeof(caracter));
    while(!file.eof()){
        predictor->comprimir(caracter,contextoActual);
        contextoActual.push_back(caracter);
        if(contextoActual.length() > orden){
            contextoActual.erase(0,1);
        }
        file.read(&caracter,sizeof(caracter));
    }
    predictor->finalizarCompresion();
    file.close();
    return 0;
}

int PPMC::descomprimir(string archivoDestino){
    ofstream file;
    file.open(archivoDestino.c_str(),"a");
    predictor->inicializarDescompresion();
    int finished = 0;
    int caracter = 0;
    char c;
    string contextoActual;
    while(!finished){
        caracter = predictor->descomprimir(contextoActual);
        if(caracter > -1){
            c = (char) caracter;
            file.write((char*)&c,sizeof(c));
            contextoActual.push_back(c);
            if(contextoActual.length() > orden){
                contextoActual.erase(0,1);
            }
        }else{
            finished = 1;
        }
    }
    file.close();
}
