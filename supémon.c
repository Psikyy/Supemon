#include <stdio.h>
#include <stdlib.h>
#include "intro/intro.h"

int main() {
    char nom[50];

    printf("Veuilliez saisir votre nom : ");
    scanf("%49s", nom);

    intro(nom);

    return 0;
}