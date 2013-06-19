#ifndef CTXM1_H_
#define CTXM1_H_


//este sera el contexto -1
//en este contexto no sera falta la exclusion, ya que cada vez que entro aca tengo que reducir en 1 la probabilidad total
#include "Contexto.h"
class CtxM1:virtual public Contexto {
	public:
		CtxM1();
		~CtxM1(){};
		//por que esto tiene que estar aca???
		//de otra forma no compila
		//TODO: ve
		
		
		
		//Devuelve un 0 y disminuye en uno la frecuencia total
		//Devuelve un 1 si llego al final del archivo
		unsigned int getFrec(std::string letra);
		//este nunca se va a llamar
		void aumentarFrec(std::string letra);

	protected:
		unsigned short int probTotal;
	
};

#endif
