#ifndef COMPRESION_CTXM1_H_
#define COMPRESION_CTXM1_H_


//este sera el contexto -1
//en este contexto no sera falta la exclusion, ya que cada vez que entro aca tengo que reducir en 1 la probabilidad total
#include "compresion_Contexto.h"
#include "compresion_letraFrec.h"
#include <string>


using namespace std;

class CtxM1: public Contexto {
	public:
		CtxM1();
		~CtxM1();
		//por que esto tiene que estar aca???
		//de otra forma no compila
		//TODO: ve
		//Devuelve un 0 y disminuye en uno la frecuencia total
		//Devuelve un 1 si llego al final del archivo
		//unsigned int getFrec(char letra,std::string letrasContexto);
		//este nunca se va a llamar
		void aumentarFrec(unsigned  char letra,std::string letrasContexto){ } ;
		//unsigned int getTotal(std::list<letraFrec>, std::string letrasContexto){return 0; };
		//Devuelve en el campo probaTotal 257 - la cantidad de caracteres incluidos
		//en el campo probaCaracter siempre tengo un 1
		probabilidades getProbabilidades(unsigned char letra, std::string letrasContexto,ListaExclusion *listaExclusion);

		probabilidades getProbabilidadesEscape(std::string letrasContexto,ListaExclusion *listaExclusion);

		int extraerCaracter(unsigned short probaAcumulada, std::string contextoActual, ListaExclusion *listaExclusion);

	protected:
		unsigned short int probTotal;
};

#endif
