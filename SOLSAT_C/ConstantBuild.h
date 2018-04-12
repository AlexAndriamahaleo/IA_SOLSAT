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

    void displayVariablesOccurence();

    void displayCbInstance();

    const vector<int> &getVariablesOccurence() const;

    void setVariablesOccurence(const vector<int> &variablesOccurence);

private:
    vector<vector< int > > clausesToLitterals ;
    vector<vector< int > > litteralsToClauses ;
    vector< int > variablesOccurence ;
    int nbClauses ;
    int nbLitterals ;
    int nbVariables ;

};


#endif //SOLSAT_C_CONSTANTBUILD_H
