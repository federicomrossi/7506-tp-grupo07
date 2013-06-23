#include "testPPMC.h"
#include "compresion_PPMC.h"
#include <fstream>

int testPPMC(){
    PPMC* ppmc = new PPMC(5,"aComprimir");
    ppmc->comprimir("aComprimir");
    delete ppmc;
    ppmc = new PPMC(5,"aComprimir");
    ppmc->descomprimir("destinoDescomprimido");
    return 0;
}
