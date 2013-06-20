#include <iostream>
#include <string>
#include "Ctx0.h"

using namespace std;

Ctx0::Ctx0(){
	this->ordenContexto=0;
	this->probTotal=0;
	for (int i=0; i<MAX_NUM_CARACTERES;i++)
		caracteres[i]=0;	
}

void Ctx0::aumentarFrec(char letra,string letrasContexto){
	caracteres[(int)letra]++;
}

//void Ctx0::exclusion(list<letraFrec> listaFrecs){
//	list<letraFrec>::iterator it;
//	int cantidadDeCaracteres=0;
//	//recorro toda la lista, por cada posicion voy a tener una letra distinta a excluir, por lo tanto tambien tengo que excluir el escape tantas veces como la cantidad de letras que haya
//	for (it = listaFrecs.begin() ; it != listaFrecs.end() ; it ++){
//		char aux = it->getLetra();
//		cantidadDeCaracteres++;
//		caracteres[(int)aux]=0;
//	}
//	caracteres[MAX_NUM_CARACTERES]-=cantidadDeCaracteres;
//}

//unsigned int Ctx0::getTotal(ListaExclusion & listaExclusion,string letrasContexto){
//	unsigned int cont = 0;
//	//this->exclusion(listaFrecs);
//	for (int i=0; i<MAX_NUM_CARACTERES; i++){
//		if (!listaExclusion.estaExcluido(caracteres[(int)letra])
//			cont += caracteres[i];
//	}
//	return cont;
//}

//unsigned int Ctx0::getTotal(){
//	unsigned int cont = 0;
//	for (int i=0; i<=MAX_NUM_CARACTERES; i++)
//		cont += caracteres[i];
//	return cont;	
//}

//unsigned int Ctx0::getFrec(char letra,string letrasContexto,ListaExclusion& listaExclusion){
//	if (caracteres[(int)letra]){
//		return (caracteres[(int)letra]);
//	}else{ 
//		for(int i=0; i<MAX_NUM_CARACTERES ; i++){
//			if (!caracteres[(int)letra]){
//				listaExclusion.excluirCaracter(letra);
//			}
//		}
//		listaExclusion.persistir();
//		return (caracteres[(int)letra]);
//	}
//		//std::cout<<"la frecuencai del escape aca es: "<<caracteres[MAX_NUM_CARACTERES]<<endl;
//		unsigned int aux= caracteres[(int)letra];
//		//aumentarFrec(letra,letrasContexto);
//		if (caracteres[(int)letra] ){
//			return (caracteres[(int)letra]);
//		}
//		else{
//			//incremento el escape
//			caracteres[MAX_NUM_CARACTERES]++;
//			//CAMBIAR ESTO
//			//TODO
//			return(0);
//		}
//}


probabilidades Ctx0::getProbabilidades(char letra,string letrasContexto, ListaExclusion& listaExclusion){
	probabilidades aux;
	unsigned short int cantDistintos=0;
	unsigned int probAcum=0;
	unsigned int probCaracter=0;
	unsigned int probTotal=0;
	bool acumulo = true;
	for (int i=0; i<MAX_NUM_CARACTERES ; i++){
		if ( ((int)letra != i) && (caracteres[(int)i]!=0) ) {
			if (!listaExclusion.estaExcluido((char)i)){
				probTotal+=caracteres[(int)i];
				if (acumulo){
					probAcum+= caracteres[(int)i];
					listaExclusion.excluirCaracter((char)i);
				}
				cantDistintos++;
			}
		}
		else if((int)letra == i) {
				probTotal+=caracteres[(int)i];
				probCaracter=caracteres[(int)i];
				acumulo=false;
				if (probCaracter!=0)	
					cantDistintos++;
		}
	}
	aux.probaCaracter=probCaracter;
	aux.probaAcumulada=probAcum;
	aux.probaTotal=probTotal;
	aux.cantDistintos=cantDistintos;
	if (aux.probaCaracter==0)
		listaExclusion.persistir();
	return aux;
}

probabilidades Ctx0::getProbabilidadesEscape(string letrasContexto,ListaExclusion& listaExclusion){
	probabilidades aux;
	unsigned short int cantDistintos=0;
	unsigned int probAcum=0;
	unsigned int probTotal=0;
	for (int i=0; i<MAX_NUM_CARACTERES ; i++){
		if ( !listaExclusion.estaExcluido((char)i)) {
			probTotal+=caracteres[(int)i];
			if(caracteres[i]>0)	
				cantDistintos++;
		}
	}
	aux.probaAcumulada=probAcum;
	aux.probaTotal=probTotal;
	aux.cantDistintos=cantDistintos;
	return aux;
}
