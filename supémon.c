#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "class/player/player.h"
#include "adventure/choice/choice.h"
#include "intro/intro.h"

int main() {
    srand(time(NULL)); // Initialisation de la graine aléatoire

    // Demander le nom du joueur
    char nom[50];
    printf("Entrez votre nom: ");
    scanf("%s", nom);

    // Lancer l'introduction et récupérer le starter choisi
    int starter_choice = intro(nom);
    if (starter_choice == 0) {
        return 1; // Quitter en cas d'erreur
    }

    // Création et initialisation du joueur avec le starter choisi
    Player player;
    initialize_player(&player, nom, 1000, starter_choice);

    // S'assurer que le Supémon est bien sélectionné
    player.selected_supemon = &player.supemons[0];

    // Lancer l'aventure
    choice(&player);

    // Libération de la mémoire allouée au joueur
    free_player(&player);

    return 0;
}
