#ifndef CTX0_H_
#define CTX0_H_


#include "Contexto.h"
#include "letraFrec.h"
#include <list>
#include "CtxM1.h"
//este sera el contexto 0
//aca si tengo exclusion
#define MAX_NUM_CARACTERES 257
using namespace std;

class Ctx0: public Contexto {
	public:
		Ctx0();
		//Llamado por el getTotal, excluye de la prob total
		void exclusion(list<letraFrec>);
		//Si esta la letra en el conexto devuelvo su frecuencia e incremento su frecuencia, caso contrario me muevo al Ctx-1, aumentando la frecuencia del escape 
		unsigned int getFrec(char letra);
		//Devuelve la suma de las frecuencias de todas las letras menos las excluidas
		unsigned int getTotal(list<letraFrec>);
		//Devuelve la suma de las frecuencias de todas las letras sin contar las exclusiones
		unsigned int getTotal();
		// Aumena en 1 la frecuencia del caracter 
		void aumentarFrec(char letra);
		~Ctx0(){};
	protected:
		unsigned int probTotal;
		CtxM1  pCtxPrevio;
		// en la pos MAX_NUM_CARACTERES guardo el escape
		unsigned int caracteres[MAX_NUM_CARACTERES];
};

#endif
