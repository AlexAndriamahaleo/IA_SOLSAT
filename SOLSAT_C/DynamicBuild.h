//
// Created by alex on 21/03/18.
//

#ifndef SOLSAT_C_DYNAMICBUILD_H
#define SOLSAT_C_DYNAMICBUILD_H

#include "tools.h"

class DynamicBuild {

public:
    // Etat des clauses
    void initClauseStaes();

    void changeClauseState(int clause);
    bool isClauseSAT(int clause);

    // Longueur des clauses
    void initClauseLength();

    int getClauseLength(int clause);
    void increaseClauseLength(int clause);
    void decreaseClauseLength(int clause);
    bool isMonolitteral(int clause);

    //Etat des littéraux

private:
    vector< bool > clausesState ;
    vector< int > clausesLength ;
    vector< int > litteralState ;
};


#endif //SOLSAT_C_DYNAMICBUILD_H
