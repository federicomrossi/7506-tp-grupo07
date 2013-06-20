#ifndef CONTEXTO_H_
#define CONTEXTO_H_

#include <string>
#include <list>
#include "letraFrec.h"

//clase virtual para hacer polimorfismo
class Contexto{
	public:
		//metodo puramente virtual
		Contexto() { };
		virtual ~Contexto(){ };
		virtual unsigned int getFrec(char letra,std::string letrasContexto)=0;
		virtual void aumentarFrec(char letra,std::string letrasContexto)=0;
		virtual unsigned int getTotal(std::list<letraFrec>, std::string letrasContexto)=0;
	protected:
		short int ordenContexto;
};


//TODO: necesitaria agregar algun contexto o algo mas?

#endif
