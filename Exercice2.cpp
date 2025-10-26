#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
using namespace std;

// Structure 3D simple
struct Vec3 {
    float x, y, z;

    Vec3(float x_=0, float y_=0, float z_=0) : x(x_), y(y_), z(z_) {}

    // Soustraction de deux vecteurs
    Vec3 operator-(const Vec3& other) const {
        return Vec3(x - other.x, y - other.y, z - other.z);
    }

    // Produit scalaire
    float dot(const Vec3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // Norme
    float length() const {
        return sqrt(x*x + y*y + z*z);
    }

    // Normalisation
    Vec3 normalize() const {
        float len = length();
        if (len == 0) return Vec3();
        return Vec3(x / len, y / len, z / len);
    }
};

// Classe abstraite : Lumiere
class Lumiere {
public:
    virtual float intensite(const Vec3& position) const = 0;
    virtual ~Lumiere() = default;
};

// Lumière directionnelle
class LumiereDirectionnelle : public Lumiere {
    Vec3 direction;
    float couleur; // intensité de base

public:
    LumiereDirectionnelle(const Vec3& dir, float coul)
        : direction(dir.normalize()), couleur(coul) {}

    float intensite(const Vec3& /*position*/) const override {
        // Intensité constante pour une lumière directionnelle
        return couleur;
    }
};

// Lumière ponctuelle
class LumierePonctuelle : public Lumiere {
    Vec3 position;
    float attenuation; // facteur de diminution avec la distance
    float intensiteBase;

public:
    LumierePonctuelle(const Vec3& pos, float intensite, float att)
        : position(pos), attenuation(att), intensiteBase(intensite) {}

    float intensite(const Vec3& point) const override {
        float distance = (point - position).length();
        return intensiteBase / (1 + attenuation * distance * distance);
    }
};

// Lumière spot
class LumiereSpot : public Lumiere {
    Vec3 position;
    Vec3 direction;
    float angleOuverture; // en radians
    float intensiteBase;

public:
    LumiereSpot(const Vec3& pos, const Vec3& dir, float angle, float intensite)
        : position(pos), direction(dir.normalize()),
          angleOuverture(angle), intensiteBase(intensite) {}

    float intensite(const Vec3& point) const override {
        Vec3 versPoint = (point - position).normalize();
        float cosAngle = direction.dot(versPoint);

        // Si le point est dans le cône d’éclairage
        if (cosAngle > cos(angleOuverture))
            return intensiteBase * cosAngle;
        else
            return 0.0f;
    }
};

// Fonction de calcul global
float calculerEclairage(const Vec3& point,
                        const vector<unique_ptr<Lumiere>>& lumieres) {
    float total = 0.0f;
    for (const auto& l : lumieres)
        total += l->intensite(point);
    return total;
}

// Fonction principale
int main() {
    vector<unique_ptr<Lumiere>> lumieres;

    lumieres.push_back(make_unique<LumiereDirectionnelle>(Vec3(1, -1, 0), 0.8f));
    lumieres.push_back(make_unique<LumierePonctuelle>(Vec3(2, 2, 2), 1.5f, 0.2f));
    lumieres.push_back(make_unique<LumiereSpot>(Vec3(0, 2, 0), Vec3(0, -1, 0), M_PI / 4, 2.0f));

    vector<Vec3> points = {
        Vec3(0, 0, 0),
        Vec3(1, 1, 0),
        Vec3(0, 3, 0)
    };

    cout << "=== Calcul d'éclairage ===" << endl;
    for (const auto& p : points) {
        cout << "Point (" << p.x << ", " << p.y << ", " << p.z << ") -> "
             << "Intensité totale : " << calculerEclairage(p, lumieres) << endl;
    }

    return 0;
}
