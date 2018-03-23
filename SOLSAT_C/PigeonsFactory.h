//
// Created by alex on 20/03/18.
//

#ifndef SOLSAT_C_PIGEONSFACTORY_H
#define SOLSAT_C_PIGEONSFACTORY_H

#include "tools.h"

class PigeonsFactory {

public:
    PigeonsFactory();

    int getNbPigeons() const;

    void setNbPigeons(int nbPigeons);

    void error_how_to_pigeons(char* prgm);

    void pigeonsFactoryInstance(int nbPigeons);

private:
    int nbPigeons ;
};


#endif //SOLSAT_C_PIGEONSFACTORY_H
