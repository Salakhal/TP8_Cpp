#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <sstream>
using namespace std;

// ===============================
// Classe de base abstraite : Plugin
// ===============================
class Plugin {
public:
    virtual string nom() const = 0;
    virtual string traiter(const string& texte) = 0;
    virtual ~Plugin() = default;

    // Factory interne pour créer les bons objets
    static unique_ptr<Plugin> creerPlugin(const string& type);
};

// ===============================
// Plugin 1 : Correcteur orthographique
// ===============================
class CorrecteurOrthographique : public Plugin {
public:
    string nom() const override { return "Correcteur orthographique"; }

    string traiter(const string& texte) override {
        string resultat = texte;
        // Corrections simples
        auto remplacer = [&](const string& fautif, const string& correct) {
            size_t pos = 0;
            while ((pos = resultat.find(fautif, pos)) != string::npos) {
                resultat.replace(pos, fautif.length(), correct);
                pos += correct.length();
            }
        };
        remplacer("bonjou", "bonjour");
        remplacer("mercie", "merci");
        remplacer("sa", "ça");
        return resultat;
    }
};

// ===============================
// Plugin 2 : Traducteur anglais
// ===============================
class TraducteurAnglais : public Plugin {
public:
    string nom() const override { return "Traducteur anglais"; }

    string traiter(const string& texte) override {
        string resultat = texte;
        auto remplacer = [&](const string& fr, const string& en) {
            size_t pos = 0;
            while ((pos = resultat.find(fr, pos)) != string::npos) {
                resultat.replace(pos, fr.length(), en);
                pos += en.length();
            }
        };
        remplacer("bonjour", "hello");
        remplacer("merci", "thank you");
        remplacer("monde", "world");
        return resultat;
    }
};

// ===============================
// Plugin 3 : Analyseur de style
// ===============================
class AnalyseurStyle : public Plugin {
public:
    string nom() const override { return "Analyseur de style"; }

    string traiter(const string& texte) override {
        stringstream ss(texte);
        string phrase;
        int longues = 0;

        // Compte les phrases trop longues
        while (getline(ss, phrase, '.')) {
            if (phrase.length() > 50)
                longues++;
        }

        string resultat = texte;
        if (longues > 0)
            resultat += "\n⚠ " + to_string(longues) + " phrase(s) trop longue(s) détectée(s).";
        else
            resultat += "\n✅ Style concis.";
        return resultat;
    }
};

// ===============================
// Factory de création de plugins
// ===============================
unique_ptr<Plugin> Plugin::creerPlugin(const string& type) {
    if (type == "correcteur") return make_unique<CorrecteurOrthographique>();
    if (type == "traducteur") return make_unique<TraducteurAnglais>();
    if (type == "analyseur") return make_unique<AnalyseurStyle>();
    return nullptr;
}

// ===============================
// Fonction principale
// ===============================
int main() {
    cout << "=== Système de plugins de traitement de texte ===" << endl;
    cout << "Entrez un texte : ";
    string texte;
    getline(cin, texte);

    // Simuler un chargement dynamique
    vector<string> types = {"correcteur", "traducteur", "analyseur"};
    vector<unique_ptr<Plugin>> plugins;

    for (const auto& type : types) {
        auto plugin = Plugin::creerPlugin(type);
        if (plugin)
            plugins.push_back(move(plugin));
    }

    // Application successive des plugins
    for (auto& plugin : plugins) {
        cout << "\n--- Application du plugin : " << plugin->nom() << " ---" << endl;
        texte = plugin->traiter(texte);
        cout << texte << endl;
    }

    cout << "\n=== Traitement terminé ===" << endl;
    return 0;
}
