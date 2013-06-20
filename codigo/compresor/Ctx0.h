#ifndef CTX0_H_
#define CTX0_H_


#include "Contexto.h"
#include "letraFrec.h"
#include <string>
#include <list>
#include "CtxM1.h"
//este sera el contexto 0
//aca si tengo exclusion
#define MAX_NUM_CARACTERES 256
using namespace std;

class Ctx0: public Contexto {
	public:
		Ctx0();
		//Llamado por el getTotal, excluye de la prob total
		//void exclusion(list<letraFrec>);
		//Si esta la letra en el conexto devuelvo su frecuencia, si no esta devuelvo 0 
		//unsigned int getFrec(char letra,string letrasContexto);
		//Devuelve la suma de las frecuencias de todas las letras menos las excluidas
		//unsigned int getTotal(list<letraFrec>, string letrasContexto);
		//Devuelve la suma de las frecuencias de todas las letras sin contar las exclusiones
		//unsigned int getTotal();
		// Aumena en 1 la frecuencia del caracter 
		void aumentarFrec(char letra,string letrasContexto);


		probabilidades getProbabilidades(char letra, string letrasContexto, ListaExclusion&);

		probabilidades getProbabilidadesEscape(string letrasContexto, ListaExclusion& listaExclusion);


		~Ctx0(){};
		
	protected:

		unsigned int probTotal;
		// en la pos MAX_NUM_CARACTERES guardo el escape
		unsigned int caracteres[MAX_NUM_CARACTERES];
};

#endif
