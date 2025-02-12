# Supémon - CLI Game

Supémon est un jeu en ligne de commande inspiré de l'univers de Pokémon. Le joueur incarne un dresseur qui doit capturer, entraîner et combattre des Supémons pour devenir le meilleur !

---

# 📖 Sommaire

1. [Installation](#installation)
2. [Lancement du jeu](#lancement-du-jeu)
3. [Actions disponibles](#actions-disponibles)
4. [Système de combat](#système-de-combat)
5. [Système de sauvegarde](#système-de-sauvegarde)
6. [Documentation technique](#documentation-technique)
7. [Commandes utiles](#commandes-utiles)
8. [Prochaines fonctionnalités](#prochaines-fonctionnalités)
9. [Auteurs](#auteurs)

---

# 🛠 Installation

1. Clonez ce dépôt :
   ```sh
   git clone https://github.com/Psikyy/Supemon
   ```
2. Compilez le jeu :
   ```sh
   gcc -o supemon supémon.c adventure/choice/choice.c adventure/center/center.c adventure/shop/shop.c adventure/wild/battle.c class/player/player.c class/supemon/supemon.c intro/intro.c save/save.c -I save -I adventure/choice -I adventure/center -I adventure/shop -I adventure/wild -I class/player -I class/supemon -I intro -lm
   ```
   🔍 **Explication** :
   - `gcc` : Utilise le compilateur GCC.
   - `-o supemon` : Génère un exécutable nommé `supemon`.
   - Liste des fichiers `.c` : Code source du projet.
   - `-I` : Spécifie les dossiers contenant les fichiers `.h`.
   - `-lm` : Lie la bibliothèque mathématique (`math.h`).

3. Exécutez le jeu :
   ```sh
   ./supemon
   ```

---

## 🎮 Lancement du jeu

- Au démarrage, le joueur entre son nom et choisit un Supémon de départ.
- Il peut aussi charger une partie sauvegardée.

---

## 🏆 Actions disponibles

- **Explorer** : Affronte un Supémon sauvage.
- **Boutique** : Achète ou vend des objets.
- **Centre Supémon** : Soigne tous les Supémons gratuitement.
- **Inventaire** : Affiche et utilise des objets.
- **Quitter** : Avec ou sans sauvegarde.

---

## ⚔️ Système de combat

- **Tour par tour** : L'ordre est basé sur la vitesse du Supémon (aléatoire en cas d'égalité).
- **Actions possibles** :
  - **Attaquer** : Choisir une attaque.
  - **Changer de Supémon** : Perd son tour.
  - **Utiliser un objet** : Limité à 4 par combat.
  - **Fuir** : Chance basée sur la vitesse.
  - **Capturer** : Chance basée sur les HP restants.
- **Fin du combat** : Lorsqu'un Supémon atteint 0 HP.
- **Récompenses** : Supcoins et expérience.

---

## 💾 Système de sauvegarde

Le jeu enregistre automatiquement :
- Le nom du joueur.
- Ses Supémons et leurs statistiques.
- Son inventaire et ses Supcoins.

📌 **Fichier de sauvegarde** : `save/supemon_save.dat`  
📤 **Sauvegarde manuelle** : Disponible en quittant le jeu.

---

## 📝 Documentation technique

### 📂 Structure des fichiers
- **`main.c`** : Point d'entrée du jeu.
- **`functions.c/.h`** : Fonctions utilitaires et logiques du jeu.
- **`player.c/.h`** : Gestion du joueur, inventaire et Supémons.
- **`combat.c/.h`** : Mécaniques de combat.

### 🏅 Structures principales

#### Joueur
```c
typedef struct {
    char nom[50];
    Supemon equipe[6];
    Supemon actif;
    int supcoins;
    Objet inventaire[10];
} Joueur;
```

#### Supémon
```c
typedef struct {
    char nom[20];
    int niveau;
    int experience;
    int hp, max_hp;
    int attaque, defense;
    int esquive, precision;
    int vitesse;
    Attaque attaques[4];
} Supemon;
```

### ⚡ Mécanique de Combat
- **Initiative** : Le Supémon avec la plus haute vitesse commence.
- **Attaques** : Calcul des dégâts :
  ```c
  int degats = (attaquant.attaque * puissance) / defenseur.defense;
  ```
- **Esquive** : Basée sur précision / (précision + esquive adverse) + 0.1.
- **Capture** : Basée sur la formule :
  ```c
  float chance = (maxHP - HP) / maxHP - 0.5;
  ```

---

## 📌 Commandes utiles

📦 **Recompiler le jeu**  
```sh
gcc -o supemon supémon.c adventure/choice/choice.c adventure/center/center.c adventure/shop/shop.c adventure/wild/battle.c class/player/player.c class/supemon/supemon.c intro/intro.c save/save.c -I save -I adventure/choice -I adventure/center -I adventure/shop -I adventure/wild -I class/player -I class/supemon -I intro -lm
```


---

## 🚀 Prochaines fonctionnalités

🔜 Fonctionnalités en cours de développement :
- 🆕 Ajout de nouveaux Supémons et objets.
- 🏆 Combats d'arène avec champions.
- 📂 Amélioration du système de sauvegarde.
- 🎭 Mode multijoueur local (coop vs CPU).

---

## 👥 Auteurs

- **Arthur** - [GitHub](https://github.com/Psikyy)
- **Tom** - [GitHub](https://github.com/Taumehh)

Amusez-vous bien dans **Supémon** ! 🎮🔥  