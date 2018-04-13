//
// Created by alex on 21/03/18.
//

#include "SolsatMain.h"

int main() {

    string prefix ;
    clock_t start, end ;

    prefix = whichProblem() ;
    const char* filename = prefix.c_str() ;

    ConstantBuild initProblem;
    DynamicBuild problemInstance;
    SolutionsFromDPLL solutionInstance;

    start = clock();

    initProblem = formulasReader(filename);

    initProblem.displayClauseToLitteral();
    initProblem.displayLitteralToClause();

    problemInstance.initInstance(initProblem);
    problemInstance.displayInstance();

    bool formulaResultat = solutionInstance.solverdpll(&problemInstance, &initProblem);

    initProblem.displayClauseToLitteral();
    initProblem.displayLitteralToClause();

    problemInstance.initInstance(initProblem);
    problemInstance.displayInstance();

    solutionInstance.displayCurrentSolution();

    cout << (formulaResultat ? "SATISFAISABLE" : "UNSATISFAISABLE") << endl ;

    end = clock();

    cout << "Temps d'éxecution du programme SOLSAT - " << (float) (end-start)/CLOCKS_PER_SEC << " sec." << endl ;


    return 0;
}