#include "CtxN.h"
using namespace std;

CtxN::CtxN(short int orden){

}

CtxN::~CtxN(){
}

void CtxN::aumentarFrec(char letra,std::string letrasContexto){

}

probabilidades CtxN::getProbabilidades(char letra,std::string letrasContexto,ListaExclusion& listaExclusion){
    probabilidades probas;
	unsigned short int cantDistintos=0;
	unsigned int probAcum=0;
	unsigned int probCaracter=0;
	unsigned int probTotal=0;
	bool acumulo = true;
	map< string, list<letraFrec> >::iterator mapIt;
	mapIt=distintosContextos.find(letrasContexto);
	if (mapIt!=distintosContextos.end()){
		list <letraFrec> lista = mapIt->second;
		list <letraFrec>::iterator listIt;
		for (listIt=lista.begin() ; listIt!=lista.end() ; listIt++){
			if (letra != listIt->getLetra()) {
				if (!listaExclusion.estaExcluido(listIt->getLetra())){
					probTotal+=listIt->getFrec();
					if (acumulo){
						probAcum+=listIt->getFrec();
						listaExclusion.excluirCaracter(listIt->getLetra());
						}
					cantDistintos++;
				}
			}else if (letra == listIt->getLetra()){
				probTotal+=listIt->getFrec();
				probCaracter+=listIt->getFrec();
				acumulo = false;
				//ya no lo necesito
				//if (probCaracter!=0)
					cantDistintos++;
			}
		}
	}
	probas.probaCaracter=probCaracter;
	probas.probaAcumulada=probAcum;
	probas.probaTotal=probTotal;
	probas.cantDistintos=cantDistintos;
	if (probas.probaCaracter == 0)
		listaExclusion.persistir();
    return probas;
}

//Tener en cuenta que si cantDistintos = 0 , entonces escape = 1
probabilidades CtxN::getProbabilidadesEscape(std::string letrasContexto,ListaExclusion&){
    probabilidades probas;
	unsigned short int cantDistintos=0;
	unsigned int probAcum=0;
	unsigned int probTotal=0;
	map< string, list<letraFrec> >::iterator mapIt;
	mapIt=distintosContextos.find(letrasContexto);
	if (mapIt!=distintosContextos.end()){
		list <letraFrec> lista = mapIt->second;
		list <letraFrec>::iterator listIt;
		for (listIt = lista.begin(); listIt != lista.end() ; listIt++){
			if (!listaExclusion.estaExcluido(listIt->getChar())){
				probTotal+=listIt->getFrec();
				cantDistintos++;
			}
		}
	}
	//No se aumenta en ningun momento la prob acum !
	probas.cantDistintos=cantDistintos;
	probas.probaAcumulada=probAcum;
	probas.probaTotal=probTotal;
    return probas;
}

int CtxN::extraerCaracter(unsigned short s, std::string s2, ListaExclusion&l){
    return 0;
}
