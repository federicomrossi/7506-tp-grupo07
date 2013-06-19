#ifndef CTX0_H_
#define CTX0_H_


#include "Contexto.h"
#include "letraFrec.h"
#include <list>
//este sera el contexto 0
//aca si tengo exclusion
#define MAX_NUM_CARACTERES 257


class Ctx0: public Contexto {
	public:
		Ctx0();
		void exclusion(list<letraFrec>);
		unsigned int getFrec(std::string letra);
		//Devuelve la suma de las frecuencias de todas las letras menos las excluidas
		unsigned int getTotal(list<letraFrec>);
		void aumentarFrec(std::string letra);
		~Ctx0(){};
	protected:
		unsigned short int probTotal;
		// en la pos MAX_NUM_CARACTERES guardo el escape
		int caracteres[MAX_NUM_CARACTERES];
};

#endif
