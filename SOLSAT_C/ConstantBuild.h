//
// Created by alex on 20/03/18.
//

#ifndef SOLSAT_C_CONSTANTBUILD_H
#define SOLSAT_C_CONSTANTBUILD_H

#include "tools.h"

class ConstantBuild {

public:

    ConstantBuild();

    const vector<vector<int>> &getClausesToLitterals() const;

    void setClausesToLitterals(const vector<vector<int> > &clausesToLitterals);

    const vector<vector<int>> &getLitteralsToClauses() const;

    void setLitteralsToClauses(const vector<vector<int> > &litteralsToClauses);

    int getNbClauses() const;

    void setNbClauses(int nbClauses);

    int getNbLitterals() const;

    void setNbLitterals(int nbLitterals);

    int getNbVariables() const;

    void setNbVariables(int nbVariables);

    void displayClauseToLitteral();

    void displayLitteralToClause();


private:
    vector<vector< int > > clausesToLitterals ;
    vector<vector< int > > litteralsToClauses ;
    int nbClauses ;
    int nbLitterals ;
    int nbVariables ;

};


#endif //SOLSAT_C_CONSTANTBUILD_H
