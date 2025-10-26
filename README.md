 # TP 8 : Polymorphisme et classes virtuelles

 #  Exercice 1 : Gestion de périphériques audio

##  Objectifs pédagogiques
- Utiliser une **interface abstraite** pour unifier l’accès à différents périphériques audio.  
- Illustrer la **liaison dynamique** à travers un tableau de pointeurs.  
- Montrer la nécessité d’un **destructeur virtuel** pour éviter les fuites mémoire.

---

## Contexte
Une application doit piloter plusieurs périphériques audio :
- Haut-parleur  
- Casque Bluetooth  
- Sortie HDMI  

Tous possèdent les mêmes opérations (`ouvrir`, `jouer`, `fermer`), mais avec des implémentations spécifiques.

---

##  Fonctionnement
1. `SortieAudio` définit les méthodes virtuelles pures.  
2. Chaque sous-classe implémente ses propres versions.  
3. Le tableau de pointeurs permet d’appeler les méthodes de manière polymorphe.  
4. Le destructeur virtuel garantit la libération correcte de la mémoire.

---

##  Exemple de sortie

```
[HautParleur] Ouverture du haut-parleur.
[HautParleur] Lecture du son : Musique.mp3
[HautParleur] Fermeture du haut-parleur.
-----------------------------
[CasqueBT] Connexion Bluetooth établie.
[CasqueBT] Lecture du son : Musique.mp3
[CasqueBT] Déconnexion Bluetooth.
-----------------------------
[SortieHDMI] Canal HDMI activé.
[SortieHDMI] Lecture du son : Musique.mp3
[SortieHDMI] Canal HDMI désactivé.
-----------------------------
Destruction HautParleur
Destruction SortieAudio
Destruction CasqueBT
Destruction SortieAudio
Destruction SortieHDMI
Destruction SortieAudio

```

 ##  Exemple d’exécution (image)
 
Voici un exemple de l'exécution du programme (screenshot) : 

<img width="831" height="615" alt="image" src="https://github.com/user-attachments/assets/142d606b-7c80-4ce9-a438-65cd8ea56b36" />



#  Exercice 2 : Moteur de rendu 3D

##  Objectifs pédagogiques
- Employer des **pointeurs intelligents** (`unique_ptr`) pour la gestion automatique de la mémoire.  
- Combiner **polymorphisme** et **calcul algorithmique** (sommation d’intensité).  
- Gérer une **collection hétérogène** d’objets dérivés.

---

##  Contexte
Un moteur 3D gère plusieurs types de lumières :
- **Lumière directionnelle** : intensité constante.  
- **Lumière ponctuelle** : intensité dépend de la distance.  
- **Lumière spot** : intensité dépend de l’angle.

---


##  Fonctionnement
1. La classe `Lumiere` définit la méthode virtuelle pure `float intensite(const Vec3&)`.  
2. Chaque sous-classe redéfinit le calcul d’intensité selon son type.  
3. Les objets sont stockés dans un `std::vector<std::unique_ptr<Lumiere>>`.  
4. Une fonction `calculerEclairage()` additionne les intensités pour un point donné.

---

## Exemple de sortie
```
=== Calcul d'éclairage ===
Point (0, 0, 0) -> Intensité totale : 2.15423
Point (1, 1, 0) -> Intensité totale : 1.89956
Point (0, 3, 0) -> Intensité totale : 0.8

```
 ##  Exemple d’exécution (image)
 
Voici un exemple de l'exécution du programme (screenshot) : 

<img width="881" height="200" alt="image" src="https://github.com/user-attachments/assets/fb848c6b-38d4-4498-92ea-1ecce96f54cd" />


#  Exercice 3 : Système de plugins de traitement de texte

##  Objectifs pédagogiques
- Illustrer le **polymorphisme** dans un système extensible.  
- Utiliser une **factory interne** pour créer dynamiquement les plugins.  
- Manipuler et transformer des **chaînes de caractères** via des modules indépendants.

---

##  Contexte
Un éditeur de texte extensible via des **plugins** :
- Correcteur orthographique  
- Traducteur anglais  
- Analyseur de style  

Chaque plugin applique une transformation spécifique au texte.

---


##  Fonctionnement
1. Le texte est saisi par l’utilisateur.  
2. Le programme simule un **chargement dynamique** de plugins via la factory `creerPlugin()`.  
3. Chaque plugin transforme le texte à tour de rôle et affiche le résultat.  

---

##  Exemple d’exécution
```
=== Système de plugins de traitement de texte ===
Entrez un texte : bonjou le monde, mercie pour sa démonstration.

--- Application du plugin : Correcteur orthographique ---
bonjour le monde, merci pour ça démonstration.

--- Application du plugin : Traducteur anglais ---
hello le world, thank you pour ça démonstration.

--- Application du plugin : Analyseur de style ---
hello le world, thank you pour ça démonstration.
 Style concis.

=== Traitement terminé ===
```
 ##  Exemple d’exécution (image)
 
Voici un exemple de l'exécution du programme (screenshot) : 

<img width="967" height="497" alt="image" src="https://github.com/user-attachments/assets/ee523faf-7fdd-43cc-a347-61d26c3bc82a" />
