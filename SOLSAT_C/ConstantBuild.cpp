//
// Created by alex on 20/03/18.
//

#include "ConstantBuild.h"

ConstantBuild::ConstantBuild() = default;

const vector<vector<int>> &ConstantBuild::getClausesToLitterals() const {
    return clausesToLitterals;
}

void ConstantBuild::setClausesToLitterals(const vector<vector<int> > &clausesToLitterals) {
    ConstantBuild::clausesToLitterals = clausesToLitterals ;
}

const vector<vector<int>> &ConstantBuild::getLitteralsToClauses() const {
    return litteralsToClauses;
}

void ConstantBuild::setLitteralsToClauses(const vector<vector<int> > &litteralsToClauses) {
    ConstantBuild::litteralsToClauses = litteralsToClauses ;
}
int ConstantBuild::getNbClauses() const {
    return nbClauses;
}

void ConstantBuild::setNbClauses(int nbClauses) {
    ConstantBuild::nbClauses = nbClauses;
}

int ConstantBuild::getNbLitterals() const {
    return nbLitterals;
}

void ConstantBuild::setNbLitterals(int nbLitterals) {
    ConstantBuild::nbLitterals = nbLitterals;
}

int ConstantBuild::getNbVariables() const {
    return nbVariables;
}

void ConstantBuild::setNbVariables(int nbVariables) {
    ConstantBuild::nbVariables = nbVariables;
}


void ConstantBuild::displayClauseToLitteral() {
    cout << "displayClauseToLitteral\n"
            "=========================================\n" ;
    for (int j = 0; j < this->getClausesToLitterals().size(); ++j) {
        cout << "la clause " << j << " contient les litteraux ";
        for(const int& i : this->getClausesToLitterals()[j])
            cout << i << " ; ";
        cout << endl ;
    }
    cout << "=========================================\n" ;
}

void ConstantBuild::displayLitteralToClause(){
    cout << "displayLitteralToClause\n"
            "=========================================\n" ;
    for (int j = 0; j < this->getLitteralsToClauses().size(); ++j) {
        cout << "le litteral " << j << " apparait dans la clause ";
        for(const int& i : this->getLitteralsToClauses()[j])
            cout << i << " ; ";
        cout << endl ;
    }
    cout << "=========================================\n" ;
}







