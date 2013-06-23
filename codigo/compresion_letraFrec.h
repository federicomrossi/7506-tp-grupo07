#ifndef COMPRESION_LETRAFREC_H_
#define COMPRESION_LETRAFREC_H_

class letraFrec{
	protected:
		char letra;
		unsigned int frec;
	public:
		letraFrec(char letra);
		char getLetra();
		unsigned int getFrec();
		void aumentarFrec();	
};

#endif
