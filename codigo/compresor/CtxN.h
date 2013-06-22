//Clase abstracta para manejar los contextos superiores a 1

#ifndef CTXN_H_
#define CTXN_H_
#include <string>
#include "Contexto.h"
#include <list>
#include <map>
#include "letraFrec.h"

//declaraciones necesarias para el map


using namespace std;


class CtxN : public Contexto{
	public:
		CtxN(){};
		CtxN(short int orden);
		~CtxN();

		void aumentarFrec(char letra,std::string letrasContexto);
		//virtual unsigned int getTotal(std::list<letraFrec>, std::string letrasContexto)=0;
		probabilidades getProbabilidades(char letra,std::string letrasContexto,ListaExclusion&);
		probabilidades getProbabilidadesEscape(std::string letrasContexto,ListaExclusion&);
		int extraerCaracter(unsigned short probaAcumulada, std::string contextoActual, ListaExclusion&);

	protected:
		//ademas va a tener el orden del contexto por heredar d Contexto
		map <string, list<letraFrec> > distintosContextos;

	private:
		std::string adaptarContexto(std::string contextoActual);

		
};


#endif
