#include <stdio.h>
#include <stdlib.h>
#include "intro.h"

int game(char *nom) {
    int choice;
    int é = 130;

    printf("Hello %s !\nWelcome to the shop!\n", nom, );

    printf("+-----------------------------+\n");
    printf("|\t - what do u want to do    |\n");
    printf("|\t1 - buy                    |\n");
    printf("|\t2 - sell                   |\n");
    printf("+-----------------------------+\n");

    printf("1, or 2: ");
    if (scanf("%d", &choice) != 1) {
        printf("Erreur : entr%ce invalide !", é);
        return 0;
    }

    if (choice < 1 || choice > 2) {
        printf("Erreur : le choix n'existe pas !");
        return 0;
    }

    switch (choice) {
        case 1:
            printf("Vous avez choisi d'acheter !\n");
            break;
        case 2:
            printf("Vous avez choisi de vendre\n");
            break;
    }
    return choice;
}