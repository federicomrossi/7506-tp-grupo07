#include "compresion_Aritmetico.h"
#include <fstream>
#include <stdio.h>

/**
* Autor: Pablo Rodriguez
* Compresor aritmetico. Precision 16 bits.
*
*/

Aritmetico::Aritmetico(std::string fileDest){
    this->file = fileDest;
    this->piso = 0;
    this->techo = 0xFFFF;
    this->UF = 0;
    this->bitCount=0;
    this->bitBuffer=0;
    this->codigoDescompresion=0;
}

Aritmetico::~Aritmetico(){
}

int Aritmetico::comprimir(unsigned short probaCaracter, unsigned short probaAcumulada, unsigned short total){
    //FILE* f;
    //f=fopen("logCompresor.txt","a");
    if (total==0) {
    	return 0;
    }
    unsigned int rango = this->techo - this->piso + 1;
    this->techo = this->piso + (rango * (probaCaracter+probaAcumulada)/total) -1;
    this->piso = this->piso + (rango * probaAcumulada/total);
    //fprintf(f,"Rango: %d \n",rango);
    //fprintf(f,"Techo: %d \n",techo);
    //fprintf(f,"Piso: %d \n",piso);
    int finished = 0;
    while(!finished){
        short bitMasSignificativo= (this->techo ^ this->piso) / 0x8000;
        if(!bitMasSignificativo){ //overflow
            //fprintf(f,"Overflow \n");
            char msb = this->techo / 0x8000;//escribo bit mas significativo
            bitBuffer <<= 1;
            if(msb){
                bitBuffer = bitBuffer | 0x0001;
            }
            bitCount++;
            checkBuffer();
            while(UF > 0){
                //msb = this->piso / 0x7FFF;
                bitBuffer <<= 1;
                bitCount++;
                if(!msb){
                    bitBuffer = bitBuffer | 0x0001;
                }
                UF--;
                checkBuffer();
            }
            this->piso <<= 1;
            this->techo <<= 1;
            this->techo = this->techo | 0x0001;
            //fprintf(f,"Techo: %d \n",techo);
            //fprintf(f,"Piso: %d \n",piso);
        }else if(!(this->techo & 0x4000) && (this->piso & 0x4000)){ //verifico underflow
                //fprintf(f,"Underflow \n");
                UF++;
                this->piso = this->piso & 0x3FFF;
                this->techo = this->techo | 0x4000;
                this->piso <<= 1;
                this->techo <<= 1;
                this->techo = this->techo | 0x0001;

                //fprintf(f,"Techo: %d \n",techo);
                //fprintf(f,"Piso: %d \n",piso);
        }else{
            finished=1;
        }
    }
//    fclose(f);
    return 0;
}

int Aritmetico::finalizarCompresion(){
    char msb = this->piso / 0x8000;//escribo bit mas significativo
    bitBuffer <<= 1;
    if(msb){
        bitBuffer = bitBuffer | 0x0001;
    }
    bitCount++;
    this->piso <<= 1;
    checkBuffer();
    while(UF > 0){
        //msb = this->piso / 0x7FFF;
        bitBuffer <<= 1;
        bitCount++;
        if(!msb){
            bitBuffer = bitBuffer | 0x0001;
        }
        UF--;
        checkBuffer();
    }
    for(int i=0;i<15;i++){
        msb = this->piso / 0x8000;//escribo bit mas significativo
        bitBuffer <<= 1;
        if(msb){
            bitBuffer = bitBuffer | 0x0001;
        }
        bitCount++;
        this->piso <<= 1;
        checkBuffer();
    }
    while(bitCount<=7){
        bitCount++;
        bitBuffer<<=1;
    }
    std::ofstream fileD;
    fileD.open(this->file.c_str(),std::fstream::app);
    fileD.write((char*)&bitBuffer,sizeof(char));
    fileD.close();
    return 0;
}


int Aritmetico::inicializarDescompresion(){
    std::ifstream fileD;
    fileD.open(file.c_str(),std::fstream::in);
    unsigned char c;
    unsigned char p;
    //fileD.read((char*)&codigoDescompresion,sizeof(codigoDescompresion));
    fileD.read((char*)&c,sizeof(char));
    this->codigoDescompresion = c;
    codigoDescompresion <<= 8;
    fileD.read((char*)&p,sizeof(char));
    codigoDescompresion += p;
    fileD.read((char*)&bitBuffer,sizeof(char));
    fileD.close();
    bitCount=0;
    posDescompresion=3;
    return 0;
}



unsigned short Aritmetico::descomprimir(unsigned short total){
    unsigned short probaAcumulada = 0;
    unsigned int rango = this->techo - this->piso + 1;
    probaAcumulada = (((this->codigoDescompresion - this->piso + 1)*total-1))/rango;
    return probaAcumulada;
}

int Aritmetico::actualizarRangosDescompresion(unsigned short probaCaracter, unsigned short probaAcumulada, unsigned short total){
    // FILE* f;
    //f=fopen("logDescompresor.txt","a");
    unsigned int rango = this->techo - this->piso + 1;
    this->techo = this->piso + (rango * (probaCaracter+probaAcumulada)/total) -1;
    this->piso = this->piso + (rango * probaAcumulada/total);
    /*if(codigoDescompresion < piso || codigoDescompresion > techo){
        //fprintf(f,"//////////////////// ERROR //////////////// \n");
    }
    fprintf(f,"Codigo: %d \n",codigoDescompresion);
    fprintf(f,"Buffer: %d \n",bitBuffer);
    fprintf(f,"Rango: %d \n",rango);
    fprintf(f,"Techo: %d \n",techo);
    fprintf(f,"Piso: %d \n",piso);*/
    int finished = 0;
    while(!finished){
        short bitMasSignificativo= (this->techo ^ this->piso) / 0x8000;
        if(!bitMasSignificativo){ //overflow
            //fprintf(f,"Overflow \n");
            readBufferDescompresion();
            this->piso <<= 1;
            this->techo <<= 1;
            this->techo = this->techo | 0x0001;
            /*fprintf(f,"Techo: %d \n",techo);
            fprintf(f,"Piso: %d \n",piso);
            fprintf(f,"Codigo %d \n",codigoDescompresion);
            fprintf(f,"Buffer: %d \n",bitBuffer);*/
        }else if(!(this->techo & 0x4000) && (this->piso & 0x4000)){ //verifico underflow
                //fprintf(f,"Underflow \n");
                this->codigoDescompresion ^= 0x4000;
                this->piso = this->piso & 0x3FFF;
                this->techo = this->techo | 0x4000;
                readBufferDescompresion();
                this->piso <<= 1;
                this->techo <<= 1;
                this->techo = this->techo | 0x0001;
                /*fprintf(f,"Techo: %d \n",techo);
                fprintf(f,"Piso: %d \n",piso);
                fprintf(f,"Codigo %d \n",codigoDescompresion);
                fprintf(f,"Buffer: %d \n",bitBuffer);*/
        }else{
            finished=1;
        }
    }
    //fflush(f);
    //fclose(f);
    return 0;
}

int Aritmetico::readBufferDescompresion(){
    this->codigoDescompresion <<= 1;
    char msb = bitBuffer / 0x80;
    if(msb){
        this->codigoDescompresion = codigoDescompresion| 0x0001;
    }
    bitBuffer <<=1;
    bitCount++;
    if(bitCount > 7){
        std::ifstream fileD;
        fileD.open(file.c_str());
        fileD.seekg(posDescompresion++);
        fileD.read((char*)&bitBuffer,sizeof(char));
        if(fileD.eof()){
            bitBuffer=0;
        }
        fileD.close();
        bitCount=0;
    }
    return 0;
}

int Aritmetico::checkBuffer(){
    if(bitCount > 7){
        std::ofstream file;
        file.open(this->file.c_str(),std::fstream::app);
        file.write((char*)&bitBuffer,sizeof(char));
        file.close();
        bitBuffer = 0;
        bitCount = 0;
    }
    return 0;
}
