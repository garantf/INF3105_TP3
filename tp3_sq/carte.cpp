/*  INF3105 - Structures de données et algorithmes
 *  UQAM / Département d'informatique / TP3
 *
 *  Vos noms + codes permanents :
 */

#include <cstdio>
#include <limits>
#include <math.h>
#include <queue>
#include <map>
#include <sstream>
#include <iostream>
#include "carte.h"

using namespace std;

Carte::Carte() {
}

Carte::~Carte() {
    for (std::set<Site*>::iterator it = listeSites.begin(); it != listeSites.end(); ++it) {
        delete *it;
    }
    for (std::vector<Rue*>::iterator it = listeRues.begin(); it != listeRues.end(); ++it) {
        Rue* rue = *it;
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
    for (std::set<Site*>::iterator it = listeSites.begin(); it != listeSites.end(); ++it) {
        Site* site = *it;
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

void Carte::calculerArbreRecouvrementMinimal() {
    if (listeSites.empty()) return;

    priority_queue<pair<int, Rue*>, vector<pair<int, Rue*> >, greater<pair<int, Rue*> > > pq;
    set<Site*> dansMST;
    vector<Rue*> mstRues;
    int totalCost = 0;

    // Start with the first site in alphanumerical order
    Site* startSite = *listeSites.begin();
    dansMST.insert(startSite);

    // Initialize the priority queue with the adjacent streets of the first site
    for (vector<Rue*>::iterator it = startSite->listeRuesSite.begin(); it != startSite->listeRuesSite.end(); ++it) {
        Rue* rue = *it;
        pq.push(make_pair(rue->poids, rue));
    }

    // Main loop of Prim's algorithm
    while (!pq.empty() && dansMST.size() < listeSites.size()) {
        pair<int, Rue*> top = pq.top();
        pq.pop();
        int cost = top.first;
        Rue* rue = top.second;
        Site* siteToAdd = NULL;

        if (dansMST.count(rue->debut) > 0 && dansMST.count(rue->fin) == 0)
            siteToAdd = rue->fin;
        else if (dansMST.count(rue->debut) == 0 && dansMST.count(rue->fin) > 0)
            siteToAdd = rue->debut;

        if (siteToAdd) {
            dansMST.insert(siteToAdd);
            mstRues.push_back(rue);
            totalCost += cost;
            for (vector<Rue*>::iterator it = siteToAdd->listeRuesSite.begin(); it != siteToAdd->listeRuesSite.end(); ++it) {
                Rue* adjRue = *it;
                pq.push(make_pair(adjRue->poids, adjRue));
            }
        }
    }

    // Sort the mstRues vector in alphanumerical order
    std::sort(mstRues.begin(), mstRues.end());

    // Output results
    for (set<Site*>::iterator it = listeSites.begin(); it != listeSites.end(); ++it)
        cout << (*it)->nom << endl;
    for (vector<Rue*>::iterator it = mstRues.begin(); it != mstRues.end(); ++it)
        cout << (*it)->nom << " " << (*it)->debut->nom << " " << (*it)->fin->nom << " " << (*it)->poids << endl;
    cout << "---" << endl;
    cout << totalCost << endl;
}


istream& operator >> (istream& is, Carte& carte)
{
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

