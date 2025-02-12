# Supémon - CLI Game

Supémon est un jeu en ligne de commande inspiré de l'univers de Pokémon. Le joueur incarne un dresseur qui doit capturer, entraîner et combattre des Supémons pour devenir le meilleur !

---

## Documentation Utilisateur

### Installation
1. Clonez ce dépôt :
   ```sh
   git clone https://github.com/Psikyy/Supemon
   ```
2. La commande de compilation :
    ```sh
    gcc -o supemon supémon.c adventure/choice/choice.c adventure/center/center.c adventure/shop/shop.c adventure/wild/battle.c class/player/player.c class/supemon/supemon.c intro/intro.c -I adventure/choice -I adventure/center -I adventure/shop -I adventure/wild -I class/player -I class/supemon -I intro -lm
    ```
    Explication :
    - `gcc` : Utilise le compilateur GCC.
    - `-o supemon` : Génère un exécutable nommé `supemon`.
    - Liste des fichiers `.c` : Code source du projet.
    - `-I` : Spécifie les dossiers contenant les fichiers `.h`.
    - `-lm` : Lie la bibliothèque mathématique (`math.h`).
3. Exécutez le jeu :
   ```sh
   ./supemon
   ```

### Lancement du jeu
- Au démarrage, le joueur entre son nom et choisit un Supémon de départ.

### Actions disponibles
- **Explorer** : affronte un Supémon sauvage.
- **Boutique** : achète ou vend des objets.
- **Centre Supémon** : soigne tous les Supémons gratuitement.
- **Inventaire** : affiche et utilise des objets.
- **Quitter** : avec ou sans sauvegarde.

### Combat
- Système au tour par tour.
- Choix d'action : attaquer, changer de Supémon, utiliser un objet, fuir ou capturer un ennemi.
- Un combat se termine lorsqu'un Supémon atteint 0 HP.
- Récompenses en cas de victoire : Supcoins et expérience.

---

## Documentation Technique

### Structure des fichiers
- **main.c** : Point d'entrée du jeu, gère la boucle principale.
- **functions.c/.h** : Fonctions utilitaires et logiques du jeu.
- **player.c/.h** : Gestion du joueur, inventaire et Supémons.
- **combat.c/.h** : Mécaniques de combat.

### Structures principales
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

### Mécanique de Combat
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

## À venir
- Ajout de nouveaux Supémons.
- Plus d'objets et de mécaniques avancées.
- Possiblité de charger une partie.
- Ajout de combats d'arêne.

---

## Auteurs
- Arthur - [GitHub](https://github.com/Psikyy)
- Tom - [GitHub](https://github.com/Taumehh)

Amusez-vous bien dans Supémon ! 🎮🔥

