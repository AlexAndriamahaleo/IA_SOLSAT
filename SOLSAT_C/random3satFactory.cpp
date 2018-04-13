//
// Created by alex on 13/04/18.
//

#include "random3satFactory.h"

bool random3satFactory::generateRandomBool() {
    random_device randomDevice;
    mt19937 r(randomDevice());
    uniform_real_distribution<> myRandom(0, 1);

    double myNumber = myRandom(r);

    return myNumber > 0.5;
}

bool random3satFactory::selectRandomElement(vector<bool> myElement) {
    return false;
}

void random3satFactory::generateRandom3sat() {
    cout << "Combien de clauses voulez-vous ? >" ;
    cin >> nbClauses ;
    cout << endl ;
    cout << "Combien de variables voulez-vous ? >" ;
    cin >> nbVariables ;
    cout << endl ;

    vector<bool > var ;


    for (int i = 0; i < nbClauses; ++i) {

    }

}
