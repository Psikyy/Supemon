#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "class/player/player.h"
#include "adventure/choice/choice.h"
#include "intro/intro.h"
#include "save/save.h"  // Ajoutez cette ligne

int main() {
    srand(time(NULL));

    Player *player = NULL;
    char choix;
    
    // Menu initial
    printf("1. Nouvelle partie\n");
    printf("2. Charger une partie\n");
    printf("Votre choix: ");
    scanf(" %c", &choix);

    if (choix == '2') {
        // Essayer de charger une partie
        player = load_game("save.dat");
        if (player == NULL) {
            printf("Aucune sauvegarde trouvée. Création d'une nouvelle partie.\n");
            choix = '1';
        } else {
            printf("Partie chargée avec succès !\n");
        }
    }

    if (choix == '1') {
        // Nouvelle partie
        char nom[50];
        printf("Entrez votre nom: ");
        scanf("%s", nom);

        // Lancer l'introduction et récupérer le starter choisi
        int starter_choice = intro(nom);
        if (starter_choice == 0) {
            return 1;
        }

        // Création et initialisation du joueur
        player = (Player*)malloc(sizeof(Player));
        initialize_player(player, nom, 100000, starter_choice);
        player->selected_supemon = &player->supemons[0];
    }

    // Lancer l'aventure
    choice(player);

    // Demander si le joueur veut sauvegarder avant de quitter
    printf("Voulez-vous sauvegarder la partie ? (o/n): ");
    scanf(" %c", &choix);
    if (choix == 'o' || choix == 'O') {
        if (save_game(player, "save.dat")) {
            printf("Partie sauvegardée avec succès !\n");
        } else {
            printf("Erreur lors de la sauvegarde\n");
        }
    }

    // Libération de la mémoire
    free_player(player);
    free(player);

    return 0;
}