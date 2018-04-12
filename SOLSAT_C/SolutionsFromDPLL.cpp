//
// Created by alex on 26/03/18.
//

#include "SolutionsFromDPLL.h"

int SolutionsFromDPLL::searchMonolitteral(DynamicBuild *data, ConstantBuild *init) {
    for (int i = 0; i < init->getNbClauses(); ++i) {
        if(data->isMonolitteral(i) && !data->isClauseSAT(i)){
            cout << "La clause " << i << " contient un mono litteral" << endl ;

            for (int j : init->getClausesToLitterals()[i]) {
                if(j != abs(currentAffection.top()))
                    return j;
            }
        }
    }
    cout << "Aucun mono-littéral trouvé" << endl ;
    return -1;
}

int SolutionsFromDPLL::searchPureLitterals(DynamicBuild *data, ConstantBuild *init) {
    for (int i = 0; i < init->getNbLitterals(); ++i) {
        if(data->getLitteralState()[i] == 0){
            if((i%2) == 0){
                if(init->getVariablesOccurence()[i+1] == 0){
                    cout << "littéra pur trouvé " << i << " !!" << endl ;
                    return i ;
                }
            } else {
                if(init->getVariablesOccurence()[i-1] == 0){
                    cout << "littéra pur trouvé " << i << " !!" << endl ;
                    return i ;
                }
            }
        }
    }

    cout << "Aucun littéral pur trouvé" << endl ;

    return -1;
}

int SolutionsFromDPLL::searchFirstFail(DynamicBuild *data, ConstantBuild *init) {
    // RENVOIE L'INDICE DE LA VARIABLE À METTRE À FAUX CAR C'EST LA VARIABLE DE NÉGATION

    int firstFail = -1 ;
    int firstFail_occ = 0 ;

    for (int i = 0; i < init->getNbLitterals()/2; ++i) {
        // CHERCHE UNE VARIABLE DONT L'OPPOSÉ APPARAIT LE PLUS DANS LA BASE DE CLAUSE
        if(data->getLitteralState()[i] == 0 && init->getVariablesOccurence()[i+1] > firstFail_occ){
            //firstFail = (i*2)+1 ;
            cout << i << " n'est pas instancier et sont opposé apparait " << init->getVariablesOccurence()[i+1] << " fois dans la base de clause" << endl ;
            firstFail = i+1 ;
            firstFail_occ = init->getVariablesOccurence()[i+1] ;

        }
    }

    cout << (firstFail != -1 ? "[searchFirstFail] On a trouvé une variable -> " : "Aucune variable trouvé ") << firstFail << " + " << firstFail_occ << endl ;

    return firstFail ;
}

int SolutionsFromDPLL::searchFirstSatisfy(DynamicBuild *data, ConstantBuild *init) {
    // RENVOIE L'INDICE DE LA VARIABLE À METTRE À VRAI SI L'INDICE EST PAIR
    //                                          À FAUX SI L'INDICE EST IMPAIR

    int firstSatisfy = -1 ;
    int firstSatisfy_occ = 0 ;

    for (int i = 0; i < init->getNbLitterals(); ++i) {
        if(data->getLitteralState()[i] == 0 && init->getVariablesOccurence()[i] > firstSatisfy_occ){
            //firstSatisfy = i*2 ;
            cout << i << " n'est pas instancier et apparait " << init->getVariablesOccurence()[i] << " fois dans la base de clause" << endl ;
            firstSatisfy = i ;
            firstSatisfy_occ = init->getVariablesOccurence()[i] ;
        }
    }

    cout << (firstSatisfy != -1 ? "[searchFirstSatisfy] On a trouvé une variable -> " : "Aucune variable trouvé ") << firstSatisfy << " + " << firstSatisfy_occ <<  endl ;

    return firstSatisfy ;
}

void SolutionsFromDPLL::propagation(int litteral_i, DynamicBuild *data, ConstantBuild *init, bool is_back) {


    if( litteral_i%2 == 0){ // PAIR

        data->setLitteralState_i(litteral_i-1, 1) ; // AFFECTION DU LITTERAL i À VRAI
        // RECHERCHE DES CLAUSES QUI CONTIENNENT LE LITTERAL i ET METTRE À SAT ou UNSAT SI ON FAIT UN RETOUR EN ARRIÈRE
        for (int i : init->getLitteralsToClauses()[litteral_i]) {
            data->changeClauseState(i);
        }

        cout << "-----"
                "On diminue les clauses qui contiennent " << litteral_i+1 << endl ;

        // RECHERCHE DES CLAUSES QUI CONTIENNEENT SON OPPOSÉ, FAIRE DIMINUER LA CLAUSE DE 1
        for (int j = 0; j < init->getLitteralsToClauses()[litteral_i].size(); ++j) {

            if(!is_back)
                data->decreaseClauseLength(init->getLitteralsToClauses()[litteral_i][j]);
            else
                data->increaseClauseLength(init->getLitteralsToClauses()[litteral_i][j]);
        }

    } else { // IMPAIR

        data->setLitteralState_i(litteral_i-1, 2) ; // AFFECTION DU LITTERAL i À FAUX
        // RECHERCHE DES CLAUSES QUI CONTIENNENT LE LITTERAL i ET METTRE À SAT
        for (int i : init->getLitteralsToClauses()[litteral_i]) {
            data->changeClauseState(i);
        }

        cout << "-----"
                "On diminue les clauses qui contiennent " << litteral_i-1 << endl ;

        // RECHERCHE DES CLAUSES QUI CONTIENNEENT SON OPPOSÉ, FAIRE DIMINUER LA CLAUSE DE 1
        for (int j = 0; j < init->getLitteralsToClauses()[litteral_i-1].size(); ++j) {

            if(!is_back)
                data->decreaseClauseLength(init->getLitteralsToClauses()[litteral_i][j]);
            else
                data->increaseClauseLength(init->getLitteralsToClauses()[litteral_i][j]);
        }
    }
}

bool SolutionsFromDPLL::solverdpll(DynamicBuild *pb, ConstantBuild *init) {

    int current_variable ;
    int current_variable_fail ;
    bool is_back = false ;

    init->displayCbInstance();

    while(!pb->allVariableTested()){

        cout << "----------------- DEBUT DE BOUCLE -------------------" << endl ;

        pb->displayInstance();

        displayCurrentSolution();

        cout << "---------------------- BREAKPOINT -----------------------" << endl ;

        if(((current_variable = searchMonolitteral(pb, init)) != -1) || ((current_variable = searchPureLitterals(pb, init)) != -1)){
            cout << "On PROPAGE la variable (UNIT ou MONO) " << current_variable << " a VRAI" <<  endl ;
            // PROPAGATION MONO LITTERAL ou PROPAGATION LITERRAL PUR
            propagation(current_variable, pb, init, is_back);

            currentAffection.push(current_variable);

        } else {
            current_variable = searchFirstSatisfy(pb, init);
            current_variable_fail = searchFirstFail(pb, init);

            if(current_variable == current_variable_fail){
                cout << "FirstSatisfy == FirstFail | On PROPAGE la variable " << current_variable_fail << " a FAUX" << endl ;
                // PROPAGATION DE L'AFFECTATION À FAUX DE current_variable_fail

                propagation(current_variable_fail, pb, init, is_back);

                currentAffection.push(-current_variable_fail);


            } else if(init->getVariablesOccurence()[current_variable] > init->getVariablesOccurence()[current_variable_fail]){
                cout << "On PROPAGE la variable " << current_variable << " a VRAI" << endl ;
                // PROPAGATION DE L'AFFECTATION À VRAI DE current_variable

                propagation(current_variable, pb, init, is_back);

                currentAffection.push(current_variable);


            } else {
                cout << "On PROPAGE la variable " << current_variable_fail << " a FAUX" << endl ;
                // PROPAGATION DE L'AFFECTATION À FAUX DE current_variable_fail

                propagation(current_variable_fail, pb, init, is_back);

                currentAffection.push(-current_variable_fail);

            }
        }


        if(pb->containsEmptyClause() ){
            // INITIATION AU RETOUR EN ARRIÈRE
            /*
             * depile()
             * S'IL RESTE AFFECTATION POSSIBLE :    changeAffectation() de la variable dépiler
             *                                      empile()
             *                                      propage()
             * SINON :                              dépile()
             *                                      on recommence
             */

            is_back = true ;

            cout << "IL Y A UNE CLAUSE VIDE - INITIATION AU RETOUR EN ARRIÈRE"  << endl ;

            //return false;
        }

        //return false;
        cout << "----------------- FIN DE BOUCLE -------------------" << endl ;
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

void SolutionsFromDPLL::displayCurrentSolution() {
    cout << "Solution courrante :" << endl ;
    for (stack<int> dump = currentAffection; !dump.empty(); dump.pop())
        cout << dump.top() << '\n';
}

