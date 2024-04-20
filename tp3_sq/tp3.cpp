/*  INF3105 - Structures de données et algorithmes
    UQAM / Département d'informatique, TP3
*/

#include <fstream>
#include <iostream>
#include <string>
#include <math.h>
#include "carte.h"

using namespace std;

void tp3(Carte& carte){
    carte.calculerArbreRecouvrementMinimal();
}

int main(int argc, const char** argv)
{
  
    if(argc!=2){
        cout << "Syntaxe: ./tp3 exemple.txt" << endl;
        return 1;
    }

    Carte carte;
    {
        ifstream fichiercarte(argv[1]);
        if(fichiercarte.fail()){
            cout << "Erreur ouverture du fichier : " << argv[1] << endl;    
            return 1;
        }
        fichiercarte >> carte;
    }

    tp3(carte);
    return 0;
}
