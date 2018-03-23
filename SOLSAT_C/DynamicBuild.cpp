//
// Created by alex on 21/03/18.
//

#include "DynamicBuild.h"

void DynamicBuild::initClauseLength() {

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

void DynamicBuild::initClauseStaes() {

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




