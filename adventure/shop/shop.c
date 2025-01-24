#include <stdio.h>
#include <stdlib.h>
#include "adventure/choice/choice.h"


int shop() {
    int choix;
    int é = 130;

    if(choice() == 2) {
        printf("+-----------------------------+\n");
        printf("|Welcome to the shop !        |\n");
        printf("|\t1 - Buy a items            |\n");
        printf("|\t2 - Sell a items           |\n");
        printf("+-----------------------------+\n");

        printf("1 or 2: ");

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
            buy();
        case 2:
            printf("Vous avez choisi le starter num%cro 2, vous poss%cdez donc Supasaur !\n", é, é);
            break;
        case 3:
            printf("Vous avez choisi le starter num%cro 3, vous poss%cdez donc Supmander !\n", é, é);
            break;
        case 4:
            printf("Vous avez choisi le starter num%cro 3, vous poss%cdez donc Supmander !\n", é, é);
            break;
        }
        return choix;

    }
}

int buy() {
    int items_num;
    int é = 130;
    char resp;

    printf("+-----------------------------+\n");
    printf("|Welcome to the shop !        |\n");
    printf("|\t1 - Potion (100 Supcoins)  |\n");
    printf("|\t2 - Super Potion (300 Supcoins)|\n");
    printf("|\t3 - Rare Candy (700 Supcoins)  |\n");
    printf("|\t4 - Go Back  |\n");
    printf("+-----------------------------+\n");

    printf("1, 2 or 3 : ");
    
    if (scanf("%d", &items_num) != 1) {
            printf("Erreur : entr%ce invalide !", é);
            return 0;
        }

        if (items_num < 1 || items_num > 4) {
            printf("Erreur : cette option n'existe pas !");
            return 0;
        }

    if(items_num == 1) {
        printf("The potion add + 5 HP on your Supémon.");
        printf("Are you sure to buy this item ? (Y or N) : ");
        if(scanf("%c", &resp) == 'Y' || scanf("%c", &resp) == 'y') {
            printf("1 Potion are add in your inventory !");
            buy();
        } else if (resp == 'N' || resp == 'n')
        {
            buy();
        }
    }
    if(items_num == 2) {
        printf("The super-potion add + 10 HP on your Supémon.");
        printf("Are you sure to buy this item ? (Y or N) : ");
        if(scanf("%c", &resp) == 'Y' || scanf("%c", &resp) == 'y') {
            printf("1 Super-Potion are add in your inventory !");
            buy();
        } else if (resp == 'N' || resp == 'n')
        {
            buy();
        }

    if(items_num == 3) {
        printf("The Rare Candy adds a level to the Supémon.");
        printf("Are you sure to buy this item ? (Y or N) : ");
        if(scanf("%c", &resp) == 'Y' || scanf("%c", &resp) == 'y') {
            printf("1 Rare Candy are add in your inventory !");
            buy();
        } else if (resp == 'N' || resp == 'n')
        {
            buy();
        }

    if(items_num == 4) {
         shop();
    }
}
}
}

int sell() {
    int items_num;
    int é = 130;
    char resp;

    printf("+-----------------------------+\n");
    printf("|Welcome to the shop !        |\n");
    printf("|\t1 - Potion (100 Supcoins)  |\n");
    printf("|\t2 - Super Potion (300 Supcoins)|\n");
    printf("|\t3 - Rare Candy (700 Supcoins)  |\n");
    printf("|\t4 - Go Back  |\n");
    printf("+-----------------------------+\n");

    printf("1, 2 or 3 : ");
    
    if (scanf("%d", &items_num) != 1) {
            printf("Erreur : entr%ce invalide !", é);
            return 0;
        }

        if (items_num < 1 || items_num > 4) {
            printf("Erreur : cette option n'existe pas !");
            return 0;
        }

    if(items_num == 1) {
        printf("Are you sure to sell this item ? (Y or N) : ");
        if(scanf("%c", &resp) == 'Y' || scanf("%c", &resp) == 'y') {
            printf("1 Potion are remove in your inventory !");
            buy();
        } else if (resp == 'N' || resp == 'n')
        {
            buy();
        }
    }
    if(items_num == 2) {
        printf("Are you sure to sell this item ? (Y or N) : ");
        if(scanf("%c", &resp) == 'Y' || scanf("%c", &resp) == 'y') {
            printf("1 Super-Potion are remove in your inventory !");
            buy();
        } else if (resp == 'N' || resp == 'n')
        {
            buy();
        }

    if(items_num == 3) {
        printf("Are you sure to sell this item ? (Y or N) : ");
        if(scanf("%c", &resp) == 'Y' || scanf("%c", &resp) == 'y') {
            printf("1 Rare Candy are remove in your inventory !");
            buy();
        } else if (resp == 'N' || resp == 'n')
        {
            buy();
        }

    if(items_num == 4) {
         shop();
    }
}
}
}