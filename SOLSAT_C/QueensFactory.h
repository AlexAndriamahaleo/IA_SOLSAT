//
// Created by alex on 20/03/18.
//

#ifndef SOLSAT_C_QUEENSFACTORY_H
#define SOLSAT_C_QUEENSFACTORY_H

#include "tools.h"

class QueensFactory {

public:
    QueensFactory();

    int getNbQueens() const;

    void setNbQueens(int nbQueens);

    void error_how_to_queens(char* prgm);

    void queensFactoryInstance(int nbQueens);

private:
    int nbQueens ;
};


#endif //SOLSAT_C_QUEENSFACTORY_H
