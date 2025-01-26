#include <stdio.h>
#include <stdlib.h>
#include "shop.h"
#include "../choice/choice.h"

int shop() {
    int choix;
    int é = 130;

    printf("+-----------------------------+\n");
    printf("| Welcome to the shop!        |\n");
    printf("|\t1 - Buy an item            |\n");
    printf("|\t2 - Sell an item           |\n");
    printf("|\t3 - Exit shop              |\n");
    printf("+-----------------------------+\n");

    printf("1, 2 or 3: ");

    if (scanf("%d", &choix) != 1) {
        printf("Erreur : entr%ce invalide !\n", é);
        return 0;
    }

    switch (choix) {
        case 1:
            buy();
            break;
        case 2:
            sell();
            break;
        case 3:
            choice();
            break;
        default:
            printf("Erreur : cette option n'existe pas !\n");
            break;
    }

    return choix;
}

int buy() {
    printf("You bought an item!\n");
    return 0;
}

int sell() {
    printf("You sold an item!\n");
    return 0;
}
