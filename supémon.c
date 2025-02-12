#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "class/player/player.h"
#include "adventure/choice/choice.h"
#include "intro/intro.h"

int main() {
    srand(time(NULL)); // Initialisation de la graine aléatoire

    Player player;
    char choice2;
    char nom[50]; // Déclaration du nom avant de l'utiliser

    printf("Voulez-vous charger une sauvegarde ? (o/n) : ");
    scanf(" %c", &choice2);

    if (choice2 == 'o' || choice2 == 'O') {
        load_player(&player, "savegame.txt");

        // Vérifier si un Supémon est sélectionné après chargement
        if (player.supemon_count > 0) {
            player.selected_supemon = &player.supemons[0];
        }
    } else {
        printf("Entrez votre nom : ");
        scanf("%s", nom);

        int starter_choice = intro(nom);
        if (starter_choice == 0) {
            return 1; // Quitter en cas d'erreur
        }

        // Initialisation du joueur avec le starter choisi
        initialize_player(&player, nom, 100000, starter_choice);

        // S'assurer que le Supémon est bien sélectionné
        player.selected_supemon = &player.supemons[0];
    }

    // Lancement du jeu
    choice(&player);

    // Sauvegarde avant de quitter
    save_player(&player, "savegame.txt");

    // Libération de la mémoire allouée au joueur
    free_player(&player);

    return 0;
}
