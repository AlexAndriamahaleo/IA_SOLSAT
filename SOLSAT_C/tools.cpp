//
// Created by alex on 20/03/18.
//

#include "tools.h"

string resolveFromFile(char* pb, int n_pb){

    int n ;
    string response ;

    string prefix ;

    string prefix_p = "../SOLSAT_C/pigeons/";
    string prefix_p_o = "../SOLSAT_C/pigeons/pigeonsCnf-";

    string prefix_q = "../SOLSAT_C/dames/" ;
    string prefix_q_o = "../SOLSAT_C/dames/queensCnf-";

    string ext = ".cnf" ;

    cout << "Voulez-vous lire une instance CNF pour le problème n-" << pb << " ? OUI | NON\n"
            "       (?) Si vous souhaitez créer une instance du problème, répondez non.\n > " ;
    cin >> response ;

    if(n_pb == 1){
        if(response.find("ui") != std::string::npos){
            cout << "Quel est le nom de votre fichier ? > " ;
            cin >> response ;
            prefix_p += response ;
            prefix += prefix_p ;
        } else {
            cout << "Vous avez choisis de générer une nouvelle instance du problème n-" << pb <<".\n"
                    "----------------------------------------\n"
                    "Veuillez entrez le nombre de " << pb <<".\n"
                         " > " ;
            cin >> n ;

            cout << "Génération du problème en cours..." << endl ;

            PigeonsFactory pigeonsFactory ;
            pigeonsFactory.setNbPigeons(n);
            pigeonsFactory.pigeonsFactoryInstance(pigeonsFactory.getNbPigeons());
            //pigeonsFactory.pigeonsFactoryInstance(n);

            prefix += prefix_p_o ;
            prefix += to_string(n);
            prefix += ext ;
        }
    } else {
        if(response.find("ui") != std::string::npos) {
            cout << "Quel est le nom de votre fichier ? > ";
            cin >> response;
            prefix_q += response;
            prefix += prefix_q ;
        } else {
            cout << "Vous avez choisis de générer une nouvelle instance du problème n-" << pb <<".\n"
                    "----------------------------------------\n"
                    "Veuillez entrez le nombre de " << pb <<".\n"
                         " > " ;
            cin >> n ;

            cout << "Génération du problème en cours..." << endl ;

            QueensFactory queensFactory ;
            queensFactory.setNbQueens(n);
            queensFactory.queensFactoryInstance(queensFactory.getNbQueens());

            //queensFactoryInstance(n);

            prefix += prefix_q_o ;
            prefix += to_string(n);
            prefix += ext ;
        }
    }

    return prefix ;
}

string whichProblem(){
    string pb ;
    cout << "Quel problème voulez-vous résoudre ? pigeons | dames\n > " ;
    cin >> pb ;

    if(!strcmp(pb.c_str(),"pigeons")){
        return resolveFromFile((char*)pb.c_str(), 1);
    } else if (!(strcmp(pb.c_str(), "dames"))){
        return resolveFromFile((char*)pb.c_str(), 2);
    } else {
        cout << "Erreur dans le choix du problème\n" ;
        exit(1);
    }
}

