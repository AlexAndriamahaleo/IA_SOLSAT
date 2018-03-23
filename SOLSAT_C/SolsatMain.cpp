//
// Created by alex on 21/03/18.
//

#include "SolsatMain.h"

int main() {

    string prefix ;

    /*if(!(strcmp(argv[1],"pigeons"))){

        cout << "Voulez-vous lire une instance CNF pour le problème n-pigeons ? OUI | NON\n"
                "       (?) Si vous souhaitez créer une instance du problème, répondez non.\n > " ;
        cin >> response ;

        //response = resolveFromFileOrNot(argv[1]);

        if(response.find("ui") != std::string::npos){
            prefix = "../SOLSAT/pigeons/" ;
            cout << "Quel est le nom de votre fichier ? > " ;
            cin >> response ;
            prefix += response ;
        } else {
            cout << "Vous avez choisis de générer une nouvelle instance du problème n-pigeons.\n"
                    "----------------------------------------\n"
                    "Veuillez entrez le nombre de pigeons.\n"
                    " > " ;
            cin >> n ;

            cout << "Génération du problème en cours..." << endl ;

            pigeonsFactoryInstance(n);

            string pigeons = "../SOLSAT/pigeons/pigeonsCnf-" ;
            string pg_ext = ".cnf" ;

            prefix += pigeons ;
            prefix += to_string(n);
            prefix += pg_ext ;
        }



    } else if(!(strcmp(argv[1],"queens"))){

        string prefix_queen = "../SOLSAT/queens/" ;
        cout << "Quel est le nom de votre fichier ? > " ;
        cin >> response ;
        prefix += response ;

    } else {
        error_how_to(argv[0]);
    }*/

    prefix = whichProblem() ;
    const char* filename = prefix.c_str() ;

    ConstantBuild initProblem;

    initProblem = formulasReader(filename);

    initProblem.displayClauseToLitteral();
    initProblem.displayLitteralToClause();

    return 0;
}