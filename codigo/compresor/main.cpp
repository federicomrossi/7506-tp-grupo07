#include "PPMC.h"
using namespace std;

int main(){

	PPMC ppmc(1,"test");
	ppmc.comprimir("test.txt");
	ppmc.descomprimir("test.descomp");
	return 0;

}
