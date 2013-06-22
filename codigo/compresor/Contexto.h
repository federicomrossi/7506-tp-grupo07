#ifndef CONTEXTO_H_
#define CONTEXTO_H_

#include <string>
#include <list>
#include "letraFrec.h"
#include "ListaExclusion.h"
#define MAX_NUM_CARACTERES 257
//clase virtual para hacer polimorfismo


struct probabilidades {

	unsigned short int probaCaracter;
	unsigned short int probaAcumulada;
	unsigned short int probaTotal;
	unsigned short int cantDistintos;
};


class Contexto{
	public:
		//metodo puramente virtual
		Contexto() { };
		virtual ~Contexto(){ };
		//virtual unsigned int getFrec(char letra,std::string letrasContexto,ListaExclusion&)=0;
		virtual void aumentarFrec(char letra,std::string letrasContexto)=0;
		//virtual unsigned int getTotal(std::list<letraFrec>, std::string letrasContexto)=0;
		virtual probabilidades getProbabilidades(char letra,std::string letrasContexto,ListaExclusion&)=0;
		virtual probabilidades getProbabilidadesEscape(std::string letrasContexto,ListaExclusion&)=0;
		virtual int extraerCaracter(unsigned short probaAcumulada, std::string contextoActual, ListaExclusion&)=0;
	protected:
		short int ordenContexto;
};




#endif
