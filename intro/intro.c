#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "intro.h"

int intro(char *nom) {
    setlocale(LC_ALL, ""); // Permet l'utilisation de caractères UTF-8
    
    printf("Hello %s !\nWelcome to Supémon World!\n", nom);

    printf("+-----------------------------+\n");
    printf("|Choose your starter Supémon: |\n");
    printf("|\t1 - Supmander         |\n");
    printf("|\t2 - Supasaur          |\n");
    printf("|\t3 - Supirtle          |\n");
    printf("+-----------------------------+\n");

    int starter;
    printf("1, 2 or 3: ");
    while (scanf("%d", &starter) != 1 || starter < 1 || starter > 3) {
        printf("Invalid input! Please enter a number between 1 and 3: ");
        while (getchar() != '\n');
    }
    system("clear");

    switch (starter) {
        case 1:
            printf("Vous avez choisi le starter numéro 1, vous possédez donc Supmander !\n");
            break;
        case 2:
            printf("Vous avez choisi le starter numéro 2, vous possédez donc Supasaur !\n");
            break;
        case 3:
            printf("Vous avez choisi le starter numéro 3, vous possédez donc Supirtle !\n");
            break;
    }
    return starter;
}