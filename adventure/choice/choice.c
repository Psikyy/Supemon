#include <stdio.h>
#include <stdlib.h>
#include "adventure/shop/shop.h"

int choice() {
    int choix;
    int é = 130;

    printf("+-----------------------------+\n");
    printf("|Where do you want to go?     |\n");
    printf("|\t1 - Into the wild          |\n");
    printf("|\t2 - Into the shop          |\n");
    printf("|\t3 - In the Supémon Center  |\n");
    printf("|\t4 - Leave the Game         |\n");
    printf("+-----------------------------+\n");

    printf("1, 2, 3 or 4: ");

    if (scanf("%d", &choix) != 1) {
        printf("Erreur : entr%ce invalide !", é);
        return 0;
    }

    if (choix < 1 || choix > 4) {
        printf("Erreur : cette option n'existe pas !");
        return 0;
    }

    switch (choix) {
        case 1:
            printf("Vous avez choisi le starter num%cro 1, vous poss%cdez donc Supmander !\n", é, é);
            break;
        case 2:
            shop();
        case 3:
            printf("Vous avez choisi le starter num%cro 3, vous poss%cdez donc Supmander !\n", é, é);
            break;
        case 4:
            printf("Vous avez choisi le starter num%cro 3, vous poss%cdez donc Supmander !\n", é, é);
            break;
    }
    return choix;
}