#include "CtxN.h"

CtxN::CtxN(short int orden){
	ordenContexto = orden;
}

CtxN::~CtxN(){
}

void CtxN::aumentarFrec(char letra,std::string letrasContexto){
}

probabilidades CtxN::getProbabilidades(char letra,std::string letrasContexto,ListaExclusion&){
    probabilidades probas;
    return probas;
}

probabilidades CtxN::getProbabilidadesEscape(std::string letrasContexto,ListaExclusion&){
    probabilidades probas;
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
