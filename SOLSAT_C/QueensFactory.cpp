//
// Created by alex on 20/03/18.
//

#include "QueensFactory.h"

QueensFactory::QueensFactory() = default;

int QueensFactory::getNbQueens() const {
    return nbQueens;
}

void QueensFactory::setNbQueens(int nbQueens) {
    QueensFactory::nbQueens = nbQueens;
}

void QueensFactory::error_how_to_queens(char* prgm){
    cout << "Usage: " << prgm << " n \nOù n est est le nombre de dames." << endl ;
}

int factorial(int n)
{
    if(n > 1)
        return n * factorial(n - 1);
    else
        return 1;
}

int nbCombinaisons(int nbElements){
    return ( factorial(nbElements)/(factorial(2)*factorial(nbElements-2)) ) ;
}

int nbClausesCnf(int nbDames){
    int posibility_rows_col = 2*nbDames ;
    int rows_col = 2*(nbDames*nbCombinaisons(nbDames));
    //cout << "Combinaison pour lignes et colonnes: " << rows_col << endl ;
    int diag_spe =  2*(nbCombinaisons(nbDames));
    //cout << "Combinaison pour les grandes diagonales: " << diag_spe << endl ;
    int other_diag = 0 ;
    for (int i = nbDames-1; i != 1; i--) {
        other_diag += 4*nbCombinaisons(i);
        //cout << "Combinaison de " << i << " éléments | autre diag: " << other_diag << endl;
    }
    return posibility_rows_col + rows_col + diag_spe + other_diag ;
}

void QueensFactory::queensFactoryInstance(int nbQueens){

    int i, j, k;

    cout << "queens Factory Instance Class" << endl ;

    ofstream fileout ;
    string queens = "../SOLSAT_C/dames/queensCnf-" ;
    string qs_ext = ".cnf" ;

    //this->setNbQueens(nbQueens);
    //this->queensInstance.setNbLitterals(nbQueens*nbQueens);

    string name;
    const char* fileout_name;
    name += queens ;
    name += to_string(nbQueens) ;
    name += qs_ext ;
    fileout_name = name.c_str() ;

    fileout.open(fileout_name);

    if (!(fileout.is_open())) {
        cout << "Erreur fileout !!" << endl;
        exit(1);
    }

    cout << "Le fichier " << fileout_name << " a été créer et est ouvert" << endl ;

    fileout << "c Problème de dames \n"
            "\n"
            "c Fichier générer par QueensFactory.cpp\n"
            "\n"
            "c Par Alex ANDRIAMAHALEO\n"
            "\n"
            "c queensCnf-" << nbQueens << ".cnf\n"
                    "\n"
                    "p cnf " << nbQueens*nbQueens << " " << nbClausesCnf(nbQueens) <<
            "\n\n";

    int nbClause = 0 ;

    for (i=1; i <= nbQueens; i++)
    {
        for (j=1; j <= nbQueens; j++)
            fileout << (nbQueens)*(i-1)+j << " " ;
        fileout << 0 << endl ;
        nbClause++ ;
    }

    fileout << endl ;

    for (i=1; i <= nbQueens; i++)
    {
        for (j=1; j <= nbQueens; j++)
            fileout << ((nbQueens)*(j-1)+i) << " " ;
        fileout << 0 << endl ;
        nbClause++ ;
    }

    fileout << endl ;

    for (j=1; j <= nbQueens; j++)
        for (i=1; i <= nbQueens; i++)
            for (k=i+1; k <= nbQueens; k++){
                fileout << "-"<< (nbQueens)*(i-1)+j << " -" << (nbQueens)*(k-1)+j << " 0" << endl ;
                nbClause++ ;
            }

    fileout << endl ;

    for (j=1; j <= nbQueens; j++)
        for (i=1; i <= nbQueens; i++)
            for (k=i+1; k <= nbQueens; k++){
                fileout << "-"<< (nbQueens)*(j-1)+i << " -" << (nbQueens)*(j-1)+k << " 0" << endl ;
                nbClause++ ;
            }

    fileout << endl ;


    int step ;

    for (int l = 1; l < nbQueens*nbQueens; ++l) {
        step = l+1 ;
        for (j=nbQueens; j < nbQueens*nbQueens; j+=nbQueens){
            if(j+step <= nbQueens*nbQueens && l%nbQueens != 0 && (j+step)%nbQueens != 1){
                //cout << (j+step)%nbQueens << " - " << l%nbQueens << " - " << l << endl ;
                fileout << "-"<< l << " -" << j+step << " 0" << endl ;
                nbClause++ ;
                step++ ;
            }
        }
    }

    fileout << endl ;

    for (int m = 1; m < nbQueens * nbQueens; ++m) {
        step = m-1 ;
        for (int l = nbQueens; l < nbQueens*nbQueens; l+=nbQueens) {
            if(m%nbQueens != 1 && l+step <= nbQueens*nbQueens && (l+step)%nbQueens != 0){
                //cout << m << " - " << l+step  << " - " << l << endl;
                fileout << "-"<< m << " -" << l+step << " 0" << endl ;
                nbClause++ ;
                step-- ;
            }
        }
    }

    //cout << "nombre de clause écrite: " << nbClause << endl ;

    fileout.close();

}