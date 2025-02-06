#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "intro.h"

int intro(char *nom) {
    int starter;
    int é = 130;

    printf("Hello %s !\nWelcome to Sup%cmon World!\n", nom, é);

    printf("+-----------------------------+\n");
    printf("|Choose your starter Sup%cmon: |\n", é);
    printf("|\t1 - Supmander         |\n");
    printf("|\t2 - Supasaur          |\n");
    printf("|\t3 - Supirtle          |\n");
    printf("+-----------------------------+\n");

    printf("1, 2 or 3: ");
    
    if (scanf("%d", &starter) != 1 || starter < 1 || starter > 3) {
        printf("Entrée invalide ! Un Supémon aléatoire sera attribué.\n");
        
        srand(time(NULL));
        starter = (rand() % 3) + 1;
    }

    switch (starter) {
        case 1:
            printf("Vous avez choisi Supmander !\n");
            break;
        case 2:
            printf("Vous avez choisi Supasaur !\n");
            break;
        case 3:
            printf("Vous avez choisi Supirtle !\n");
            break;
    }
    
    return starter;
}