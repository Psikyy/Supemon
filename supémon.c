#include <stdio.h>
#include <stdlib.h>
#include "intro/intro.h"
#include "class/player/player.h"
#include "game/game_menu.h"

int main() {
    Player joueur;
    char nom[50];

    printf("Veuillez saisir votre nom : ");
    scanf("%49s", nom);

    int starter_choice = intro(nom);
    printf("Starter choisi : %d\n", starter_choice);

    initialize_player(&joueur, nom, 500, starter_choice);
    printf("Player initialisé, nom : %s\n", joueur.name);  // Vérifie si le nom est correctement affecté

    int game_running = 1;
    while (game_running) {
        // Afficher menu et gérer les actions
        game_running = game_menu(&joueur);
    }

    printf("Fin du jeu. Merci d'avoir joué !\n");

    return 0;
}