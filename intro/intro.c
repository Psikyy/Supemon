#include <stdio.h>
#include <stdlib.h>
#include "intro.h"

int intro(char *nom) {
    int starter;
    int é = 130;

    printf("Hello %s !\nWelcome to Sup%cmon World!\n", nom, é);

    printf("+-----------------------------+\n");
    printf("|Choose your starter Sup%cmon: |\n", é);
    printf("|\t1 - Supmander         |\n");
    printf("|\t2 - Supasaur          |\n");
    printf("|\t3 - Supirtle         |\n");
    printf("+-----------------------------+\n");

    printf("1, 2 or 3: ");
    if (scanf("%d", &starter) != 1) {
        printf("Erreur : entr%ce invalide !", é);
        return 0;
    }

    if (starter < 1 || starter > 3) {
        printf("Erreur : le starter n'existe pas !");
        return 0;
    }

    switch (starter) {
        case 1:
            printf("Vous avez choisi le starter num%cro 1, vous poss%cdez donc Supmander !\n", é, é);
            break;
        case 2:
            printf("Vous avez choisi le starter num%cro 2, vous poss%cdez donc Supasaur !\n", é, é);
            break;
        case 3:
            printf("Vous avez choisi le starter num%cro 3, vous poss%cdez donc Supirtle !\n", é, é);
            break;
    }
    return starter;
    system("clear");
}