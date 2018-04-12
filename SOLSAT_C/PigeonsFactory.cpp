//
// Created by alex on 20/03/18.
//

#include "PigeonsFactory.h"

PigeonsFactory::PigeonsFactory() = default;

int PigeonsFactory::getNbPigeons() const {
    return nbPigeons;
}

void PigeonsFactory::setNbPigeons(int nbPigeons) {
    PigeonsFactory::nbPigeons = nbPigeons;
}

void PigeonsFactory::error_how_to_pigeons(char* prgm){
    cout << "Usage: " << prgm << " n \nOù n est est le nombre de pigeons." << endl ;
}

void PigeonsFactory::pigeonsFactoryInstance(int nbPigeons){
    int n;
    int i, k;
    int j;
    //char* pEnd;

    n = nbPigeons ;

    if (n < 1)
        error_how_to_pigeons((char *)"pigeonsFactoryInstance");

    ofstream fileout ;
    string pigeons = "../SOLSAT_C/pigeons/pigeonsCnf-" ;
    string pg_ext = ".cnf" ;
    string name;
    const char* fileout_name;
    name += pigeons ;
    name += to_string(nbPigeons) ;
    name += pg_ext ;
    fileout_name = name.c_str() ;

    //cout << fileout_name << endl ;

    fileout.open(fileout_name);

    if (!(fileout.is_open())) {
        cout << "Erreur fileout !!" << endl;
        exit(1);
    }

    cout << "Le fichier " << fileout_name << " a été créer et est ouvert" << endl ;

    fileout << "c Problème de pigeons \n"
            "\n"
            "c Fichier générer par PigeonsFactory.cpp\n"
            "\n"
            "c Par Alex ANDRIAMAHALEO\n"
            "\n"
            "c pigeonsCnf-" << nbPigeons << ".cnf\n"
                    "\n"
                    "p cnf " << n*(n-1) <<
            " " << (2*n + (n-1)*((n-1)*n/ 2))-1 <<
            "\n\n";


    //fileout << n << endl ;

    for (i=1; i <= n; i++) // chaque pigeon...
    {
        for (j=1; j <= n-1; j++) // ...est placé dans un des nids.
            fileout << (n-1)*(i-1)+j << " " ;
        fileout << 0 << endl ;
    }

    fileout << endl ;

    for (i=1; i <= n-1; i++)
    {
        for (j=1; j <= n; j++)
            fileout << ((n-1)*(j-1)+i) << " " ;
        fileout << 0 << endl ;
    }

    fileout << endl ;

    for (j=1; j <= n-1; j++)
        for (i=1; i <= n-1; i++)
            for (k=i+1; k <= n; k++)
                fileout << "-"<< (n-1)*(i-1)+j << " -" << (n-1)*(k-1)+j << " 0" << endl ;

    fileout.close();

    cout << "Le fichier est prêt" << endl ;
}

/*int main(int argc, char** argv) {

    PigeonsFactory pigeonsFactory ;

    pigeonsFactory.setNbPigeons(4);

    pigeonsFactory.pigeonsFactoryInstance(pigeonsFactory.getNbPigeons());

    return 0 ;
}*/