#include <stdio.h>
#include <stdlib.h>
#include "intro.h"

int game() {
    int choice;
    int é = 130;

    printf("where do u want to go\n", é);

    printf("+-----------------------------+\n");
    printf("|\t1 - Into the wild          |\n");
    printf("|\t2 - To the Supemon Center  |\n");
    printf("|\t3 - To the Shop            |\n");
    printf("|\t4 - Quit                   |\n");
    printf("+-----------------------------+\n");

    printf("1, 2, 3 or 4: ");
    if (scanf("%d", &choice) != 1) {
        printf("Erreur : entr%ce invalide !", é);
        return 0;
    }

    if (choice < 1 || choice > 4) {
        printf("Erreur : le choix n'existe pas !");
        return 0;
    }

    switch (starter) {
        case 1:
            printf("Vous avez choisi de vous rendre dans la Nature !\n", é, é);
            break;
        case 2:
            printf("Vous avez choisi de vous rendre au Sup%cmon center!\n", é, é);
            break;
        case 3:
            printf("Vous avez choisi de vous rendre au Shop !\n");
            break;
        case 4:
            printf("Vous avez choisi de quitter le jeux !\n");
            break;
    }
    return choice;
}