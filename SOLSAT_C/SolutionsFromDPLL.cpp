//
// Created by alex on 26/03/18.
//

#include "SolutionsFromDPLL.h"

int SolutionsFromDPLL::searchMonolitteral(DynamicBuild data, ConstantBuild init) {
    for (int i = 0; i < init.getNbClauses(); ++i) {
        if(data.isMonolitteral(i) && !data.isClauseSAT(i))
            return i ;
    }
    cout << "Aucun mono-littéral trouvé" << endl ;
    return -1;
}

int SolutionsFromDPLL::searchPureLitterals(DynamicBuild data, ConstantBuild init) {
    for (int i = 0; i < init.getNbLitterals(); ++i) {
        if(data.getLitteralState()[i] == 0){
            if((i%2) == 0){
                if(init.getVariablesOccurence()[i+1] == 0){
                    cout << "littéra pur trouvé " << i << " !!" << endl ;
                    return i ;
                }
            } else {
                if(init.getVariablesOccurence()[i-1] == 0){
                    cout << "littéra pur trouvé " << i << " !!" << endl ;
                    return i ;
                }
            }
        }
    }

    cout << "Aucun littéral pur trouvé" << endl ;

    return -1;
}

int SolutionsFromDPLL::searchFirstFail(DynamicBuild data, ConstantBuild init) {
    // RENVOIE L'INDICE DE LA VARIABLE À METTRE À FAUX CAR C'EST LA VARIABLE DE NÉGATION

    int firstFail = -1 ;
    int firstFail_occ = 0 ;

    for (int i = 0; i < init.getNbLitterals(); ++i) {
        if(data.getLitteralState()[i] == 0 && init.getVariablesOccurence()[i+1] > firstFail_occ){
            //firstFail = (i*2)+1 ;
            //cout << i << " n'est pas instancier et sont opposé apparait " << init.getVariablesOccurence()[i+1] << " fois dans la base de clause" << endl ;
            firstFail = i+1 ;
            firstFail_occ = init.getVariablesOccurence()[i+1] ;

        }
    }

    cout << (firstFail != -1 ? "[searchFirstFail] On a trouvé une variable -> " : "Aucune variable trouvé ") << firstFail << " + " << firstFail_occ << endl ;

    return firstFail ;
}

int SolutionsFromDPLL::searchFirstSatisfy(DynamicBuild data, ConstantBuild init) {
    // RENVOIE L'INDICE DE LA VARIABLE À METTRE À VRAI SI L'INDICE EST PAIR
    //                                          À FAUX SI L'INDICE EST IMPAIR

    int firstSatisfy = -1 ;
    int firstSatisfy_occ = 0 ;

    for (int i = 0; i < init.getNbLitterals(); ++i) {
        if(data.getLitteralState()[i] == 0 && init.getVariablesOccurence()[i] > firstSatisfy_occ){
            //firstSatisfy = i*2 ;
            //cout << i << " n'est pas instancier et apparait " << init.getVariablesOccurence()[i] << " fois dans la base de clause" << endl ;
            firstSatisfy = i ;
            firstSatisfy_occ = init.getVariablesOccurence()[i] ;
        }
    }

    cout << (firstSatisfy != -1 ? "[searchFirstSatisfy] On a trouvé une variable -> " : "Aucune variable trouvé ") << firstSatisfy << " + " << firstSatisfy_occ <<  endl ;

    return firstSatisfy ;
}

int SolutionsFromDPLL::firstVariableNotInstentiated(DynamicBuild data, ConstantBuild init) {
    for (int i = 0; i < init.getNbLitterals(); ++i) {
        if(data.getLitteralState()[i] == 0){
            cout << "Variable " << i+1 << " va être instancier [NORMAL]"  << endl ;
            return i ;
        }
    }
    cout << "Aucune variable trouvé" << endl ;
    return -1 ;
}


bool SolutionsFromDPLL::solverdpll(DynamicBuild pb, ConstantBuild init) {

    int current_variable ;
    int current_variable_fail ;

    //init.displayCbInstance();

    while(!pb.allVariableTested()){

        if(pb.containsEmptyClause()){
            // INITIATION AU RETOUR EN ARRIÈRE
            /*
             * depile()
             * S'IL RESTE AFFECTATION POSSIBLE :    changeAffectation() de la variable dépiler
             *                                      empile()
             *                                      propage()
             * SINON :                              dépile()
             *                                      on recommence
             */
            return false;
        }

        if(((current_variable = searchMonolitteral(pb, init)) != -1) || ((current_variable = searchPureLitterals(pb, init)) != -1)){
            cout << "La variable " << current_variable << " va être instancier" << endl ;
            // PROPAGATION MONO LITTERAL ou PROPAGATION LITERRAL PUR




        } else {
            current_variable = searchFirstSatisfy(pb, init);
            current_variable_fail = searchFirstFail(pb, init);

            if(current_variable == current_variable_fail){
                cout << "FirstSatisfy == FirstFail " << current_variable << " - " << current_variable_fail << endl ;
                // PROPAGATION DE L'AFFECTATION À FAUX DE current_variable_fail




            } else if(init.getVariablesOccurence()[current_variable] > init.getVariablesOccurence()[current_variable_fail]){
                cout << "On choisit " << current_variable << " > " << current_variable_fail << endl ;
                // PROPAGATION DE L'AFFECTATION À VRAI DE current_variable




            } else {
                cout << "On choisit " << current_variable << " < " << current_variable_fail << endl ;
                // PROPAGATION DE L'AFFECTATION À FAUX DE current_variable_fail



            }
        }

        return false;
    }

    return true ;
}

void SolutionsFromDPLL::saveSolution(stack<int> sol) {

    cout << "taille de la pile - " << sol.size() << endl ;
    vector<int> aff ;

    while( !sol.empty() ){
        aff.push_back(sol.top());
        sol.pop() ;
    }
    this->solutions.push_back(aff);
}

void SolutionsFromDPLL::displayAllSolution() {
    for (int i = 0; i < this->solutions.size(); ++i) {
        displayOneSolution(i);
    }
}

void SolutionsFromDPLL::displayOneSolution(int i) {
    cout << "Solution " << i << " : ";
    for (int j : this->solutions[i]) {
        cout << j << " " ;
    }
    cout << endl ;
}

