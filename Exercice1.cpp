#include <iostream>
#include <string>
using namespace std;


// Classe de base abstraite
class SortieAudio {
public:
    // Méthodes virtuelles pures (interface)
    virtual void ouvrir() = 0;
    virtual void jouer(const string& son) = 0;
    virtual void fermer() = 0;

    // Destructeur virtuel pour éviter les fuites mémoire
    virtual ~SortieAudio() {
        cout << "Destruction SortieAudio" << endl;
    }
};

// Classe dérivée : HautParleur
class HautParleur : public SortieAudio {
public:
    void ouvrir() override {
        cout << "[HautParleur] Ouverture du haut-parleur." << endl;
    }
    void jouer(const string& son) override {
        cout << "[HautParleur] Lecture du son : " << son << endl;
    }
    void fermer() override {
        cout << "[HautParleur] Fermeture du haut-parleur." << endl;
    }
    ~HautParleur() {
        cout << "Destruction HautParleur" << endl;
    }
};

// Classe dérivée : Casque Bluetooth
class CasqueBT : public SortieAudio {
public:
    void ouvrir() override {
        cout << "[CasqueBT] Connexion Bluetooth établie." << endl;
    }
    void jouer(const string& son) override {
        cout << "[CasqueBT] Lecture du son : " << son << endl;
    }
    void fermer() override {
        cout << "[CasqueBT] Déconnexion Bluetooth." << endl;
    }
    ~CasqueBT() {
        cout << "Destruction CasqueBT" << endl;
    }
};

// Classe dérivée : Sortie HDMI
class SortieHDMI : public SortieAudio {
public:
    void ouvrir() override {
        cout << "[SortieHDMI] Canal HDMI activé." << endl;
    }
    void jouer(const string& son) override {
        cout << "[SortieHDMI] Lecture du son : " << son << endl;
    }
    void fermer() override {
        cout << "[SortieHDMI] Canal HDMI désactivé." << endl;
    }
    ~SortieHDMI() {
        cout << "Destruction SortieHDMI" << endl;
    }
};

// Fonction polymorphe
void tester(SortieAudio* sortie) {
    sortie->ouvrir();
    sortie->jouer("Musique.mp3");
    sortie->fermer();
    cout << "-----------------------------" << endl;
}

// Fonction principale
int main() {
    const int N = 3;
    SortieAudio* sorties[N];

    sorties[0] = new HautParleur();
    sorties[1] = new CasqueBT();
    sorties[2] = new SortieHDMI();

    for (int i = 0; i < N; ++i) {
        tester(sorties[i]);
    }

    // Libération mémoire (grâce au destructeur virtuel)
    for (int i = 0; i < N; ++i) {
        delete sorties[i];
    }

    return 0;
}
