#ifndef CTX1_H_
#define CTX1_H_
#include "CtxN.h"
#include "letraFrec.h"
#include <string>
using namespace std;
bool fncomp (string a, string b){return a<b;}

struct classcomp{
	bool operator() (const string a, const string b) const 
		{return a<b;}
};


class Ctx1: public CtxN{
	public:
		Ctx1();	
		~Ctx1(){ };
		unsigned int getFrec(string letra, string letrasContexto);
		unsigned int getTotal(list<letraFrec> , string letrasContexto);
		void aumentarFrec(string letra, string letrasContexto);
		void exclusion(list<letraFrec>);
			

};
#endif
