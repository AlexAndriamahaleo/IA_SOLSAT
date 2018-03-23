//
// Created by alex on 20/03/18.
//

#include "FormulasReader.h"

ConstantBuild formulasReader(const char* filename){

    ifstream myReadFile;
    myReadFile.open(filename);

    if (!(myReadFile.is_open())) {
        cout << "["<< filename << "] Erreur fichier !!" << endl;
        exit(1) ;
    }

    ConstantBuild myProblem ;

    vector< vector < int > > myClauses ;
    vector<int > clause ;
    vector<int > litteral ;

    vector< vector < int > > myLitterals ;
    vector<int > litterals ;

    bool flag = true ;
    long int cnf ;
    int rows = 0 ;
    long int floorIndex = 0 ;
    char * pch;

    for( string line; getline( myReadFile, line ); )
    {
        if(line[0] != 'c')
        {

            if(line[0] != 'p')
            {

                if(strlen(line.c_str()) != 0){

                    //cout << "clause - " << rows << endl;

                    pch = strtok((char *)line.c_str()," ");

                    while (pch != nullptr)
                    {
                        //int tmp = atoi(pch);
                        long int tmp = strtol(pch, &pch, 10);

                        if(tmp > 0 || tmp < 0){
                            litteral.push_back((int) tmp);

                            if(tmp > 0){
                                floorIndex = (tmp - 1)*2 ;

                                //cout << "insertion de " << rows << " dans " << floorIndex << endl;
                                //pb_tmp = myProblem.getClausesToLitterals() ;
                                //pb_tmp[floorIndex].push_back(rows);

                                myLitterals[floorIndex].push_back(rows);

                            } else {
                                floorIndex = (((tmp)*2)+1)*(-1) ;

                                //cout << "insertion de " << rows << " dans " << floorIndex%2 << endl;
                                //myVariables.myLitterals[floorIndex].push_back(rows);

                                myLitterals[floorIndex].push_back(rows);

                            }
                        } else {

                            myClauses.push_back(litteral);

                            //myProblem.myClause.push_back(litteral);

                            litteral.clear() ;
                        }

                        pch = strtok (nullptr, " ");
                    }
                    rows++ ;
                }


            } else {

                pch = strtok((char *)line.c_str()," ");
                while (pch != nullptr)
                {
                    cnf = strtol(pch, &pch, 10);

                    if(cnf){
                        if(flag){
                            //myProblem.nbVariables = (int) cnf ;
                            myProblem.setNbVariables((int) cnf);
                            myProblem.setNbLitterals(myProblem.getNbVariables()*2);

                            //cout << myProblem.getNbVariables() << " - " << myProblem.getNbLitterals() << endl ;

                            //myVariables.nbLitterals = myProblem.nbVariables*2 ;
                            //myVariables.nbVariables = myProblem.nbVariables ;
                            for (int i = 0; i < myProblem.getNbLitterals(); ++i) {
                                //myVariables.myLitterals.push_back(litterals);
                                //pb_tmp = myProblem.getLitteralsToClauses() ;
                                //pb_tmp.push_back(litterals);

                                myLitterals.push_back(litterals);

                                //myProblem.setLitteralsToClauses(litterals);
                            }
                        } else
                            myProblem.setNbClauses((int) cnf) ;
                        flag = !flag ;
                    }

                    pch = strtok (nullptr, " ");
                }
            }

        }
    }

    myProblem.setLitteralsToClauses(myLitterals);
    myProblem.setClausesToLitterals(myClauses);

    cout << "Nombre de variables:" << myProblem.getNbVariables() << endl;
    cout << "Nombre de clauses: " << myProblem.getNbClauses() << endl;


    /*myProblem.displayClauseToLitteral();
    cout << endl ;
    myProblem.displayLitteralToClause();*/

    myReadFile.close();

    return myProblem ;
}

/*int main(int argc, char** argv) {

    ConstantBuild myProblem;

    myProblem = formulasReader("../SOLSAT_C/pigeons/pigeonsCnf-4.cnf");

    myProblem.displayClauseToLitteral();
    myProblem.displayLitteralToClause();

    return 0 ;
}*/
