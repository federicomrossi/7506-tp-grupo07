//Clase abstracta para manejar los contextos superiores a 1

#ifndef CTXN_H_
#define CTXN_N_
#include <string>
#include "Contexto.h"
#include <list>
#include <map>
#include "letraFrec.h"

//declaraciones necesarias para el map


using namespace std;


class CtxN {
	public:
		CtxN() { };
		virtual unsigned int getFrec(char letra,string letrasContexto)=0;
		//Devuelve la suma de las frecuencias de todas las letras menos las excluidas
		virtual unsigned int getTotal(list<letraFrec>,string letrasContexto)=0;
		virtual void aumentarFrec(char letra,string letrasContexto)=0;
		virtual void exclusion(list<letraFrec>)=0;
		virtual ~CtxN()	{ };
	protected:
		//ademas va a tener el orden del contexto por heredar d Contexto 
		short int ordenContexto;
		map <string, list<letraFrec> > distintosContextos;
};


#endif 
