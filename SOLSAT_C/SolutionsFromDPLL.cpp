//
// Created by alex on 26/03/18.
//

#include "SolutionsFromDPLL.h"

int SolutionsFromDPLL::searchMonolitteral(DynamicBuild *data, ConstantBuild *init) {
    // RENVOIE LA VARIABLE À INSTANCIER

    for (int i = 0; i < init->getNbClauses(); ++i) {
        if(data->isMonolitteral(i) && !data->isClauseSAT(i)){

            for (int j : init->getClausesToLitterals()[i]) {

                if(!isInSolution(abs(j)))
                    return transformVariableToIndex(j) ;
            }
        }
    }
    cout << "Aucun mono-littéral trouvé" << endl ;
    return -1;
}

int SolutionsFromDPLL::searchPureLitterals(DynamicBuild *data, ConstantBuild *init) {
    // RENVOIE L'INDICE D'UN LITTÉRAUX

    for (int i = 0; i < init->getNbLitterals(); ++i) { // POUR TOUS LES LITTÉRAUX

        if(data->getLitteralState()[i] == 0){ // S'IL N'EST PAS ENCORE INSTANCIÉ

            if((i%2) == 0){ // QU'IL EST PAIR (NORMAL)

                if(init->getVariablesOccurence()[i+1] == 0){
                    return i ;
                }
            } else { // QU'IL EST IMPAIR (NÉGATION)

                if(init->getVariablesOccurence()[i-1] == 0){
                    return i ;
                }
            }
        }
    }

    return -1;
}

int SolutionsFromDPLL::searchFirstFail(DynamicBuild *data, ConstantBuild *init) {

    // RENVOIE L'INDICE DE LA VARIABLE À METTRE À FAUX CAR C'EST LA VARIABLE DE NÉGATION

    int firstFail = -1 ;
    int firstFail_occ = 0 ;
    int tmp ;

    for (int i = 0; i < init->getNbLitterals(); i+=2) {

        // CHERCHE UNE VARIABLE DONT L'OPPOSÉ APPARAIT LE PLUS DANS LA BASE DE CLAUSE

        tmp = (i/2)+1 ;

        if(data->getLitteralState()[i/2] == 0 && init->getVariablesOccurence()[i+1] > firstFail_occ && !isInSolution(tmp)){
            // PAS INSTANCIÉ ET QUE SON OCCURENCE EST SUPÉRIEUR À CELUI EN COURS

            firstFail = i+1 ;
            firstFail_occ = init->getVariablesOccurence()[i+1] ;

        }
    }


    return firstFail ;
}

int SolutionsFromDPLL::searchFirstSatisfy(DynamicBuild *data, ConstantBuild *init) {

    // RENVOIE L'INDICE DE LA VARIABLE À METTRE À VRAI SI L'INDICE EST PAIR
    //                                          À FAUX SI L'INDICE EST IMPAIR

    int firstSatisfy = -1 ;
    int firstSatisfy_occ = 0 ;
    int tmp ;

    for (int i = 0; i < init->getNbLitterals(); ++i) {

        if(i%2 == 0){
            tmp = (i/2)+1 ;
        } else {
            tmp = ((i-1)/2)+1 ;
        }

        if(data->getLitteralState()[i] == 0 && init->getVariablesOccurence()[i] > firstSatisfy_occ && !isInSolution(tmp)){


            firstSatisfy = i ;
            firstSatisfy_occ = init->getVariablesOccurence()[i] ;
        }
    }


    return firstSatisfy ;
}

int SolutionsFromDPLL::transformVariableToIndex(int litteral) {
    int true_litteral_i ;

    if(litteral < 0){
        true_litteral_i = ((abs(litteral)-1)*2)+1 ;
        //cout << litteral << " devient " << true_litteral_i << endl ;
    }
    else{
        true_litteral_i = ((litteral-1)*2) ;
        //cout << litteral << " devient " << true_litteral_i << endl ;
    }

    return true_litteral_i ;
}

int SolutionsFromDPLL::propagation(int litteral_i, DynamicBuild *data, ConstantBuild *init, bool is_back) {

    // REÇOIS L'INDICE DE LA VARIABLE QUI DOIT ÊTRE AFFECTÉ

    int indexToVariable ;

    if(litteral_i%2 == 0){ // SI L'INDICE REÇU EST PAIR -> AFFECTATION DU LITTERAL NORMAL

        indexToVariable = (litteral_i/2)+1 ;

        data->setLitteralState_i(indexToVariable-1, 1) ; // AFFECTION DU LITTERAL i À VRAI


        // RECHERCHE DES CLAUSES QUI CONTIENNENT LE LITTERAL i ET METTRE À SAT ou UNSAT SI ON FAIT UN RETOUR EN ARRIÈRE


        for (int i : init->getLitteralsToClauses()[litteral_i])
            data->changeClauseState(i);


        // RECHERCHE DES CLAUSES QUI CONTIENNEENT SON OPPOSÉ, FAIRE DIMINUER LA CLAUSE DE 1


        for (int j = 0; j < init->getLitteralsToClauses()[litteral_i+1].size(); ++j) {

            if(!is_back && !data->isClauseSAT(init->getLitteralsToClauses()[litteral_i+1][j])){

                data->decreaseClauseLength(init->getLitteralsToClauses()[litteral_i+1][j]);
            }
            else
                data->increaseClauseLength(init->getLitteralsToClauses()[litteral_i+1][j]);
        }

    } else { // SI L'INDICE REÇU EST IMPAIR -> AFFECTATION DE LA NÉGATION DU LITTERAL

        indexToVariable = ((litteral_i-1)/2)+1 ;

        data->setLitteralState_i(indexToVariable-1, 2) ; // AFFECTION DU LITTERAL i À FAUX

        // RECHERCHE DES CLAUSES QUI CONTIENNENT LE LITTERAL i ET METTRE À SAT

        for (int i : init->getLitteralsToClauses()[litteral_i])
            data->changeClauseState(i);

        // RECHERCHE DES CLAUSES QUI CONTIENNEENT SON OPPOSÉ, FAIRE DIMINUER LA CLAUSE DE 1

        for (int j = 0; j < init->getLitteralsToClauses()[litteral_i-1].size(); ++j) {

            if(!is_back && !data->isClauseSAT(init->getLitteralsToClauses()[litteral_i-1][j])){

                data->decreaseClauseLength(init->getLitteralsToClauses()[litteral_i-1][j]);
            }
            else
                data->increaseClauseLength(init->getLitteralsToClauses()[litteral_i-1][j]);
        }
    }

    return indexToVariable ;
}

bool SolutionsFromDPLL::solverdpll(DynamicBuild *pb, ConstantBuild *init) {

    int current_variable ;
    int current_variable_fail ;
    bool is_back = false ;
    int depile_var ;


    while(!pb->allVariableTested()){


        if(((current_variable = searchMonolitteral(pb, init)) != -1) || ((current_variable = searchPureLitterals(pb, init)) != -1)){
            // PROPAGATION MONO LITTERAL ou PROPAGATION LITERRAL PUR

            if(current_variable%2 == 0)
                currentAffectation.push_front(propagation(current_variable, pb, init, is_back));
            else
                currentAffectation.push_front(-propagation(current_variable, pb, init, is_back));

        } else {


            current_variable = searchFirstSatisfy(pb, init); // RENVOIE L'INDICE D'UNE VARIABLE VARIABLE


            current_variable_fail = searchFirstFail(pb, init); // RENVOIE L'INDICE DE LA VARIABLE À METTRE À FAUX

            if(current_variable == -1 || current_variable_fail == -1)
                break ;


            if(current_variable == current_variable_fail){ // SI MÊME INDICE

                // PROPAGATION DE L'AFFECTATION À FAUX DE current_variable_fail

                currentAffectation.push_front(-propagation(current_variable_fail, pb, init, is_back));


            } else if(init->getVariablesOccurence()[current_variable] > init->getVariablesOccurence()[current_variable_fail]){
                // SI L'OCCURENCE DE [FirstSatisfy] EST PLUS GRANDE OU ÉGAL À L'OCCURENCE DE [FirstFail] , ON PROPAGE [FirstSatisfy]

                // PROPAGATION DE L'AFFECTATION À VRAI DE current_variable

                currentAffectation.push_front(propagation(current_variable, pb, init, is_back));


            } else {
                // SINON ON PROPAGE [FirstFail]

                // PROPAGATION DE L'AFFECTATION À FAUX DE current_variable_fail

                currentAffectation.push_front(-propagation(current_variable_fail, pb, init, is_back));

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


            depile_var = currentAffectation.front() ;
            currentAffectation.pop_front();

            if(depile_var > 0){
                // AFFECTATION DE LA VARIABLE AU NÉGATIF
                current_variable = ((depile_var-1)*2)+1 ;
                currentAffectation.push_front(-propagation(current_variable, pb, init, is_back));

            } else {
                // AFFECTATION DE LA VARIABLE AU POSITIF
                current_variable = ((depile_var)*2)+1 ;
                currentAffectation.push_front(propagation(current_variable, pb, init, is_back));
            }

            //displayCurrentSolution();

            return false;
        }

    }

    //displayCurrentSolution();
    return true ;
}

void SolutionsFromDPLL::saveSolution(stack<int> sol) {

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
    cout << "Solution :" << endl ;
    for (int i : currentAffectation) {
        cout << i << endl ;
    }
}

bool SolutionsFromDPLL::isInSolution(int litteral) { // VRAI SI LE LITTERAL A ÉTÉ INSTANCIÉ VRAI ou FAUX
    for (int i : currentAffectation) {
        if(abs(i) == litteral){
            return true ;
        }
    }
    return false ;
}

