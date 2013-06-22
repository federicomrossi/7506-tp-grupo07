#include "testPPMC.h"
#include "PPMC.h"
#include <fstream>

int testPPMC(){
    PPMC* ppmc = new PPMC(0,"aComprimir");
    ppmc->comprimir("aComprimir");
    delete ppmc;
    ppmc = new PPMC(0,"aComprimir");
    ppmc->descomprimir("aComprimir");
    return 0;
}
