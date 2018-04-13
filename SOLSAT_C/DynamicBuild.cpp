//
// Created by alex on 21/03/18.
//

#include "DynamicBuild.h"

void DynamicBuild:: initInstance(ConstantBuild pb) {

    //cout << pb.getNbClauses() << endl ;

    for (int i = 0; i < pb.getNbClauses(); ++i) {
        this->clausesState.push_back(false);
        this->clausesLength.push_back((int) pb.getClausesToLitterals()[i].size());
    }
    for (int j = 0; j < pb.getNbLitterals()/2; ++j) {
        this->litteralState.push_back(0);
    }

}


void DynamicBuild::changeClauseState(int clause){
    clausesState[clause] = !clausesState[clause] ;
    // true -> false
    // false -> true
    // true : SAT
    // false : INSAT
}

bool DynamicBuild::isClauseSAT(int clause) {
    return clausesState[clause] ;
}

bool DynamicBuild::containsEmptyClause() {
    for (int i = 0; i < clausesState.size(); ++i) {
        if(clausesLength[i] == 0 && clausesState[i] == 0){

            return true ;
        }
    }
    return false ;
}

int DynamicBuild::getClauseLength(int clause) {
    return clausesLength[clause] ;
}

void DynamicBuild::increaseClauseLength(int clause) {
    clausesLength[clause]++ ;
}

void DynamicBuild::decreaseClauseLength(int clause) {
    clausesLength[clause]-- ;
}

bool DynamicBuild::isMonolitteral(int clause) {
    return clausesLength[clause] == 1 ;
}

void DynamicBuild::exploreBranchOfLitteral(int litteral) {

    if(litteralState[litteral] == 0 || litteralState[litteral] == 1){
        litteralState[litteral]++ ;
        //return 0;
    }

    if(litteralState[litteral] == 2) {

        //return -1;
    }
}

bool DynamicBuild::allVariableTested() {
    for (int i : litteralState) {
        if(i == 0)
            return false ;
    }

    for (auto &&j : clausesState) {
        if(j == 0)
            return false ;
    }

    return true ;
}

bool DynamicBuild::isFormulaIsSAT() {
    for (int i = 0; i < this->clausesState.size(); ++i) {
        if(!this->isClauseSAT(i))
            return false; // renvoie FAUX si UNE clause est INSAT
    }
    return true ; // renvoie VRAI si toute les clauses sont SAT donc que F est vide !
}

const vector<bool> &DynamicBuild::getClausesState() const {
    return clausesState;
}

const vector<int> &DynamicBuild::getClausesLength() const {
    return clausesLength;
}

const vector<int> &DynamicBuild::getLitteralState() const {
    return litteralState;
}

void DynamicBuild::setLitteralState_i(int i, int value) {
    litteralState[i] = value ;
}

void DynamicBuild::displayInstance() {
    cout << "displayInstance\n"
            "=========================================\n" ;
    this->displayClauseState();
    cout << "=========================================\n" ;
    this->displayClauseLength();
    cout << "=========================================\n" ;
    this->displayLitteralState();
    cout << "=========================================\n" ;

}

void DynamicBuild::displayClauseState() {
    for (int i = 0; i < clausesState.size(); ++i) {
        cout << "La clause " << i << " est " << (isClauseSAT(i) ? " satisfaite" : "insatisfaite") << endl ;
    }
}

void DynamicBuild::displayClauseLength() {
    for (int j = 0; j < clausesLength.size(); ++j) {
        cout << "La clause " << j << " est de taille " << clausesLength[j] << endl ;
    }
}

void DynamicBuild::displayLitteralState() {
    for (int k = 0; k < litteralState.size(); ++k) {

        cout << "Le litteral " << k ;
        if(litteralState[k] == 0)
            cout<< " est inexploré" << endl ;

        if(litteralState[k] == 1)
            cout<< " a été exploré sur la branche POSITIVE" << endl ;

        if(litteralState[k] == 2)
            cout<< " a été exploré sur la branche NEGATIVE" << endl ;

    }
}


