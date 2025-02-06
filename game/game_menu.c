#include <stdio.h>
#include "../class/player/player.h"

int game_menu(Player *p) {
    int choix;
    
    printf("\n--- Menu du Jeu ---\n");
    printf("Bienvenue, %s !\n", p->name); // Utiliser le paramètre 'p'
    printf("1. Combat\n");
    printf("2. Quitter le jeu\n");
    printf("Votre choix : ");
    scanf("%d", &choix);

    switch (choix) {
        case 1:
            printf("Vous avez choisi de combattre !\n");
            break;
        case 2:
            printf("Vous avez choisi de quitter le jeu.\n");
            return 0; // Quitter le jeu
        default:
            printf("Choix invalide. Essayez encore.\n");
            break;
    }

    return 1; // Retourner 1 pour continuer le jeu
}
