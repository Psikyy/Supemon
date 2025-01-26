#include <stdio.h>
#include <stdlib.h>
#include "choice.h"
#include "../shop/shop.h"

int choice() {
    int choix;
    int é = 130;

    printf("+-----------------------------+\n");
    printf("| Where do you want to go?    |\n");
    printf("|\t1 - Into the wild          |\n");
    printf("|\t2 - Into the shop          |\n");
    printf("|\t3 - In the Supémon Center  |\n");
    printf("|\t4 - Leave the Game         |\n");
    printf("+-----------------------------+\n");

    printf("1, 2, 3 or 4: ");

    if (scanf("%d", &choix) != 1) {
        printf("Erreur : entr%ce invalide !\n", é);
        return 0;
    }

    switch (choix) {
        case 1:
            printf("You chose to go into the wild!\n");
            break;
        case 2:
            shop();
            break;
        case 3:
            printf("You entered the Supémon Center!\n");
            break;
        case 4:
            printf("You left the game. Goodbye!\n");
            break;
        default:
            printf("Erreur : cette option n'existe pas !\n");
            break;
    }

    return choix;
}
