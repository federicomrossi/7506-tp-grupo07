#ifndef CONTEXTO_H_
#define CONTEXTO_H_

#include <string>


//clase virtual para hacer polimorfismo
class Contexto{
	public:
		//metodo puramente virtual
		Contexto() { };
		virtual ~Contexto(){ };
		virtual unsigned int getFrec(char letra)=0;
		virtual void aumentarFrec(char letra)=0;
	protected:
		short int ordenContexto;
		//Contexto * pContextoPrevio;
};


//TODO: necesitaria agregar algun contexto o algo mas?

#endif
