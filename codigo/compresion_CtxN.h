//Clase abstracta para manejar los contextos superiores a 1

#ifndef COMPRESION_CTXN_H_
#define COMPRESION_CTXN_H_
#include <string>
#include "compresion_Contexto.h"
#include <list>
#include <map>
#include "compresion_letraFrec.h"

//declaraciones necesarias para el map


using namespace std;


class CtxN : public Contexto{
	public:
		CtxN(){};
		CtxN(short int orden);
		~CtxN();

		void aumentarFrec(unsigned char letra,std::string letrasContexto);
		//virtual unsigned int getTotal(std::list<letraFrec>, std::string letrasContexto)=0;
		probabilidades getProbabilidades(unsigned char letra,std::string letrasContexto,ListaExclusion*);
		probabilidades getProbabilidadesEscape(std::string letrasContexto,ListaExclusion*);
		int extraerCaracter(unsigned short probaAcumulada, std::string contextoActual, ListaExclusion*);

	protected:
		//ademas va a tener el orden del contexto por heredar d Contexto
		map <string, list<letraFrec> > distintosContextos;

	private:
		std::string adaptarContexto(std::string contextoActual);


};


#endif
