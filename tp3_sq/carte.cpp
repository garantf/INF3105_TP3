/*  INF3105 - Structures de données et algorithmes
 *  UQAM / Département d'informatique / TP3
 *
 *  Vos noms + codes permanents :
 */

#include <cstdio>
#include <limits>
#include <math.h>
#include <queue>
#include <sstream>
#include <iostream>
#include "carte.h"

using namespace std;

Carte::Carte() {
}

Carte::~Carte() {
    for (Site* site : listeSites) {
        delete site;
    }
    for (Rue* rue : listeRues) {
        delete rue;
    }
}

void Carte::ajouterSite(const string& nom) {
    Site* site = new Site;
    site->nom = nom;
    listeSites.insert(site);
}

void Carte::ajouterRue(const string& nom, const string& nomSite1, const string& nomSite2, int poids) {
    Site* site1 = nullptr;
    Site* site2 = nullptr;
    for (Site* site : listeSites) {
        if (site->nom == nomSite1) {
            site1 = site;
        } else if (site->nom == nomSite2) {
            site2 = site;
        }
        if (site1 && site2) {
            break;
        }   
    } 
    assert(site1 != nullptr);
    assert(site2 != nullptr);
    Rue* rue = new Rue;
    rue->nom = nom;
    rue->poids = poids;
    rue->debut = site1;
    rue->fin = site2;
    listeRues.push_back(rue);
    site1->listeRuesSite.push_back(rue);
    site2->listeRuesSite.push_back(rue);
}

istream& operator >> (istream& is, Carte& carte)
{
    Carte::Site *site1;
    string nomSite;
    is >> nomSite;
    while (nomSite != "---") {
        carte.ajouterSite(nomSite);
        is >> nomSite;
    }
    string nomRue, nomSite1, nomSite2, dp, pv;
    int poids;
    is >> nomRue;
    while (nomRue != "---") {
        is >> dp >> nomSite1 >> nomSite2 >> poids >> pv;
        assert(dp == ":");
        assert(pv == ";");
        carte.ajouterRue(nomRue, nomSite1, nomSite2, poids);
        is >> nomRue;
    }
    return is;
}

