//
// Created by alex on 13/04/18.
//

#ifndef SOLSAT_C_RANDOM3SATFACTORY_H
#define SOLSAT_C_RANDOM3SATFACTORY_H

#include "tools.h"


class random3satFactory {

public:
    bool generateRandomBool();
    bool selectRandomElement(vector<bool> myElement);
    void generateRandom3sat();

private:
    int nbClauses ;
    int nbVariables ;
};


#endif //SOLSAT_C_RANDOM3SATFACTORY_H
