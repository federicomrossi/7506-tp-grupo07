#include "CtxN.h"
using namespace std;

CtxN::CtxN(short int orden){
	this->ordenContexto = orden;
}

CtxN::~CtxN(){
}

void CtxN::aumentarFrec(char letra,string letrasContexto){
	map < string, list<letraFrec> >::iterator mapIt;
	mapIt=distintosContextos.find(adaptarContexto(letrasContexto));
	list <letraFrec> lista;
	if (mapIt!=distintosContextos.end()){
		lista = mapIt->second;
		list <letraFrec>::iterator listIt;
		for (listIt = lista.begin() ; listIt != lista.end() ; listIt++){
			if ( letra == listIt->getLetra() ) {
				listIt->aumentarFrec();
			}
		}
	}else {
		letraFrec unaLetra(letra);
		lista.push_back(unaLetra);
		distintosContextos.insert( pair < string, list <letraFrec> > (letrasContexto,lista));
	}
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
probabilidades CtxN::getProbabilidadesEscape(std::string letrasContexto,ListaExclusion& listaExclusion){
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
			if (!listaExclusion.estaExcluido(listIt->getLetra())){
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

int CtxN::extraerCaracter(unsigned short probaAcumulada, std::string contextoActual, ListaExclusion &listaExclusion){
    
	unsigned int acumulada = 0;
	std::string contextoAdapatado = this->adaptarContexto(contextoActual);
	list<letraFrec> contexto = distintosContextos[contextoAdapatado];

	for(list<letraFrec>::iterator it = contexto.begin(); it != contexto.end(); it++) {
		
		if (probaAcumulada<acumulada) {
			it--;
			return (int)(*it).getLetra();
		}

		if(!listaExclusion.estaExcluido((*it).getLetra())) {
			acumulada+=(*it).getFrec();
		}

		listaExclusion.excluirCaracter((*it).getLetra());
	}

	if (probaAcumulada<acumulada) {
		return (int)(contexto.back().getLetra());
	} else {
		listaExclusion.persistir();
		return -1;
	}
}

// Funcion privada para adpatar el contexto segun el orden en el que nos encontremos
std::string CtxN::adaptarContexto(std::string contextoActual)
{	
	std::string contextoAdapatado = contextoActual.substr(contextoActual.length()-ordenContexto);
	return contextoAdapatado;
} 
