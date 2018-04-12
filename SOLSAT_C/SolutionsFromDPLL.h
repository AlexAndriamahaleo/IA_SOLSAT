//
// Created by alex on 26/03/18.
//

#ifndef SOLSAT_C_SOLUTIONSFROMDPLL_H
#define SOLSAT_C_SOLUTIONSFROMDPLL_H

#include "tools.h"
#include "DynamicBuild.h"
#include "ConstantBuild.h"

class SolutionsFromDPLL {

public:
    int searchMonolitteral(DynamicBuild *data, ConstantBuild *init);
    int searchPureLitterals(DynamicBuild *data, ConstantBuild *init);
    int searchFirstSatisfy(DynamicBuild *data, ConstantBuild *init);
    int searchFirstFail(DynamicBuild *data, ConstantBuild *init);
    int transformVaraibleToIndex(int litteral);
    void propagation(int litteral_i, DynamicBuild *data, ConstantBuild *init, bool is_back);
    bool solverdpll(DynamicBuild *pb, ConstantBuild *init);
    void saveSolution(stack<int> sol);
    void displayAllSolution();
    void displayOneSolution(int i);
    void displayCurrentSolution();

private:
    //DynamicBuild currentInstance ;
    stack< int > currentAffection ;
    //vector< int > currentAffectation ;
    vector<vector< int >> solutions ;

};


#endif //SOLSAT_C_SOLUTIONSFROMDPLL_H
