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

            cout << "L'indice "
                 << i
                 << " de la variable n'est pas instancier et sont opposé apparait "
                 << init->getVariablesOccurence()[i+1]
                 << " fois dans la base de clause" << endl ;
            firstFail = i+1 ;
            firstFail_occ = init->getVariablesOccurence()[i+1] ;

        }
    }

    cout << (firstFail != -1 ? "[searchFirstFail] On a trouvé l'indice de la variable à mettre à FAUX -> " : "Aucune variable trouvé ") << firstFail << " occ " << firstFail_occ << endl ;

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

            cout << "L'indice "
                 << i
                 << " de la variable n'est pas instancier et apparait "
                 << init->getVariablesOccurence()[i]
                 << " fois dans la base de clause" << endl ;

            firstSatisfy = i ;
            firstSatisfy_occ = init->getVariablesOccurence()[i] ;
        }
    }

    cout << (firstSatisfy != -1 ? "[searchFirstSatisfy] On a trouvé l'indice de la variable -> " : "Aucune variable trouvé ") << firstSatisfy << " occ " << firstSatisfy_occ <<  endl ;

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


        for (int i : init->getLitteralsToClauses()[litteral_i]) {
            data->changeClauseState(i);
            cout << "[PAIR] Clause SAT - " << i << endl;
        }

        /*tmp = transformVariableToIndex(litteral_i);

        cout << "---------------- | " << tmp << endl ;
        */

        cout << "-----"
                " [PAIR] On diminue les clauses qui contiennent la négation de " << indexToVariable << endl ;

        // RECHERCHE DES CLAUSES QUI CONTIENNEENT SON OPPOSÉ, FAIRE DIMINUER LA CLAUSE DE 1


        for (int j = 0; j < init->getLitteralsToClauses()[litteral_i+1].size(); ++j) {

            if(!is_back && !data->isClauseSAT(init->getLitteralsToClauses()[litteral_i+1][j])){
                cout << "---------------- | "
                        "On diminue la clause " << init->getLitteralsToClauses()[litteral_i+1][j] << endl ;
                data->decreaseClauseLength(init->getLitteralsToClauses()[litteral_i+1][j]);
            }
            else
                data->increaseClauseLength(init->getLitteralsToClauses()[litteral_i+1][j]);
        }

    } else { // SI L'INDICE REÇU EST IMPAIR -> AFFECTATION DE LA NÉGATION DU LITTERAL

        indexToVariable = ((litteral_i-1)/2)+1 ;

        data->setLitteralState_i(indexToVariable-1, 2) ; // AFFECTION DU LITTERAL i À FAUX

        // RECHERCHE DES CLAUSES QUI CONTIENNENT LE LITTERAL i ET METTRE À SAT
        for (int i : init->getLitteralsToClauses()[litteral_i]) {
            data->changeClauseState(i);
            cout << "[IMPAIR] Clause SAT - " << i << endl;
        }

        /*tmp = transformVariableToIndex(litteral_i);

        cout << "---------------- | " << tmp << endl ;
         */

        cout << "-----"
                "[IMPAIR] On diminue les clauses qui contiennent le normal de " << indexToVariable << endl ;

        // RECHERCHE DES CLAUSES QUI CONTIENNEENT SON OPPOSÉ, FAIRE DIMINUER LA CLAUSE DE 1
        for (int j = 0; j < init->getLitteralsToClauses()[litteral_i-1].size(); ++j) {

            if(!is_back && !data->isClauseSAT(init->getLitteralsToClauses()[litteral_i-1][j])){
                cout << "---------------- | "
                        "On diminue la clause " << init->getLitteralsToClauses()[litteral_i-1][j] << endl ;
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

    //init->displayCbInstance();

    while(!pb->allVariableTested()){

        //cout << "----------------- DEBUT DE BOUCLE -------------------" << endl ;

        //pb->displayInstance();

        //displayCurrentSolution();

        //cout << "---------------------- BREAKPOINT -----------------------" << endl ;

        if(((current_variable = searchMonolitteral(pb, init)) != -1) || ((current_variable = searchPureLitterals(pb, init)) != -1)){
            // PROPAGATION MONO LITTERAL ou PROPAGATION LITERRAL PUR


            //propagation(current_variable, pb, init, is_back);

            cout << "On PROPAGE la variable (UNIT ou MONO) d'indice " << current_variable << " a VRAI" <<  endl ;

            //currentAffection.push(current_variable);
            if(current_variable%2 == 0)
                currentAffectation.push_front(propagation(current_variable, pb, init, is_back));
            else
                currentAffectation.push_front(-propagation(current_variable, pb, init, is_back));

        } else {

            //cout << init->getNbLitterals() << endl ;

            current_variable = searchFirstSatisfy(pb, init); // RENVOIE L'INDICE D'UNE VARIABLE VARIABLE


            current_variable_fail = searchFirstFail(pb, init); // RENVOIE L'INDICE DE LA VARIABLE À METTRE À FAUX

            if(current_variable == -1 || current_variable_fail == -1)
                break ;


            if(current_variable == current_variable_fail){ // SI MÊME INDICE

                cout << "FirstSatisfy == FirstFail | On PROPAGE la variable d'indice " << current_variable_fail << " a FAUX" << endl ;
                // PROPAGATION DE L'AFFECTATION À FAUX DE current_variable_fail

                //propagation(current_variable_fail, pb, init, is_back);

                //currentAffection.push(-current_variable_fail);
                currentAffectation.push_front(-propagation(current_variable_fail, pb, init, is_back));


            } else if(init->getVariablesOccurence()[current_variable] > init->getVariablesOccurence()[current_variable_fail]){
                // SI L'OCCURENCE DE [FirstSatisfy] EST PLUS GRANDE OU ÉGAL À L'OCCURENCE DE [FirstFail] , ON PROPAGE [FirstSatisfy]

                cout << "(2) On PROPAGE la variable qui a pour variable d'indice " << current_variable << " a VRAI" << endl ;
                // PROPAGATION DE L'AFFECTATION À VRAI DE current_variable

                //propagation(current_variable, pb, init, is_back);

                //currentAffection.push(current_variable);
                currentAffectation.push_front(propagation(current_variable, pb, init, is_back));


            } else {
                // SINON ON PROPAGE [FirstFail]


                cout << "(3) On PROPAGE la variable qui a pour variable d'indice " << current_variable_fail << " a FAUX" << endl ;
                // PROPAGATION DE L'AFFECTATION À FAUX DE current_variable_fail

                //propagation(current_variable_fail, pb, init, is_back);

                //currentAffection.push(-current_variable_fail);
                currentAffectation.push_front(-propagation(current_variable_fail, pb, init, is_back));

            }
        }

        //pb->displayInstance();



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

            cout << currentAffectation.front() << endl ;

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

            displayCurrentSolution();

            //return false;
        }

        displayCurrentSolution();

        //return false;
        //cout << "----------------- FIN DE BOUCLE -------------------" << endl ;
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
    cout << "Solution courante :" << endl ;
    /*for (stack<int> dump = currentAffection; !dump.empty(); dump.pop())
        cout << dump.top() << '\n';
    */
    for (int i : currentAffectation) {
        cout << i << endl ;
    }
}

bool SolutionsFromDPLL::isInSolution(int litteral) { // VRAI SI LE LITTERAL A ÉTÉ INSTANCIÉ VRAI ou FAUX
    for (int i : currentAffectation) {
        if(abs(i) == litteral){
            cout << "------------------ La variable " << abs(i) << " est déjà dans la solution" << endl ;
            return true ;
        }
    }

    cout << "La variable " << litteral << " n'est pas dans la solution" << endl ;
    return false ;
}

