//
// Created by alex on 21/03/18.
//

#ifndef SOLSAT_C_DYNAMICBUILD_H
#define SOLSAT_C_DYNAMICBUILD_H

#include "tools.h"
#include "ConstantBuild.h"

class DynamicBuild {

public:
    void initInstance(ConstantBuild pb);

    // Etat des clauses
    const vector<bool> &getClausesState() const;
    void changeClauseState(int clause);
    bool isClauseSAT(int clause);
    bool containsEmptyClause();

    // Longueur des clauses
    const vector<int> &getClausesLength() const;
    int getClauseLength(int clause);
    void increaseClauseLength(int clause);
    void decreaseClauseLength(int clause);
    bool isMonolitteral(int clause);

    //Etat des littéraux
    const vector<int> &getLitteralState() const;
    void exploreBranchOfLitteral(int litteral);


    //tools
    bool allVariableTested();
    bool isFormulaIsSAT();
    void displayClauseState();
    void displayClauseLength();
    void displayLitteralState();
    void displayInstance();


private:
    vector< bool > clausesState ;
    vector< int > clausesLength ;
    vector< int > litteralState ;
};


#endif //SOLSAT_C_DYNAMICBUILD_H
