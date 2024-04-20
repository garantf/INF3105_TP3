/*  INF3105 - Structures de données et algorithmes
 *  UQAM / Département d'informatique / TP3
 *
 *  Vos noms + codes permanents :
 */
 
#if !defined(_CARTE__H_)
#define _CARTE__H_
#include <cassert>
#include <istream>
#include <vector>
#include <string>
#include <set>

using namespace std;

class Carte{
  public:

    struct Site;

    struct Rue {
      string nom;
      int poids;
      Site *debut, *fin;

      bool operator < (const Rue& other) const {
        if (nom != other.nom)
            return nom < other.nom;
        if (debut->nom != other.debut->nom)
            return debut->nom < other.debut->nom;
        return fin->nom < other.fin->nom;
      }
    };

    struct Site {
      string nom;
      vector<Rue*> listeRuesSite;

      bool operator < (const Site& site) const {
        return nom < site.nom;
      }

      bool operator > (const Site& site) const {
        return nom > site.nom;
      }

      bool operator == (const Site& site) const {
        return nom == site.nom;
      }

    };

    Carte();
    ~Carte();
    void ajouterSite(const string& nom);
    void ajouterRue(const string& nom, const string& nomSite1, const string& nomSite2, int poids);
    void calculerArbreRecouvrementMinimal();
    void printMSTinOrder();
    

  private:

    set<Site*> listeSites;
    vector<Rue*> listeRues;



    
  friend istream& operator >> (istream& is, Carte& carte);
};

#endif

