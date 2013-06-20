#ifndef LETRAFREC_H_
#define LETRAFREC_H_

#include <string>

using namespace std;

class letraFrec{
	protected:
		string letra;
		unsigned int frec;
	public:
		letraFrec(string letra);
		string getLetra();
		unsigned int getFrec();
		void aumentarFrec();	
};

#endif
