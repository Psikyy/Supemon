#include <stdio.h>
#include <stdlib.h>
#include "choice.h"
#include "../shop/shop.h"
#include "../../class/supemon/supemon.h"
#include "../../class/player/player.h"  // Assure-toi que cette ligne est bien là
#include "../../adventure/wild/battle.h"
#include "../../adventure/center/center.h"

void print_inventory(Player *player) {
    if (!player || !player->items) {
    printf("Erreur : joueur ou inventaire non initialisé !\n");
    return;
    }

    if (player->item_count < 0 || player->item_count > MAX_ITEMS) {
    printf("Erreur : nombre d'items invalide (%d)\n", player->item_count);
    return;
    }

    if (!player->items) {
    printf("Erreur : l'inventaire du joueur n'est pas alloué !\n");
    return;
    }

    if (player->item_count == 0) {
        printf("L'inventaire est vide.\n");
    } else {
        for (int i = 0; i < player->item_count; i++) {
            printf("%d - %s (Effet: %d)\n", i, player->items[i].name, player->items[i].effect);
        }
    }
}

void choice(Player *player) {  // Correction : passage du joueur en paramètre
    int choix;

    while (1) {
        printf("+-----------------------------+\n");
        printf("| Where do you want to go?    |\n");
        printf("| 1 - Into the wild           |\n");
        printf("| 2 - Into the shop           |\n");
        printf("| 3 - In the Supémon Center   |\n");
        printf("| 4 - Leave the Game          |\n");
        printf("+-----------------------------+\n");

        //print_inventory(player);

        printf("1, 2, 3 or 4: ");
        while (scanf("%d", &choix) != 1 || choix < 1 || choix > 4) {
            printf("Invalid input! Please enter a number between 1 and 4: ");
            while (getchar() != '\n'); // Vider le buffer d'entrée
        }

        switch (choix) {
            case 1:
                system("clear");
                Supemon wild_supemon = get_random_wild_supemon(player);
                battle(&wild_supemon, player);
                break;
            case 2:
                system("clear");
                shop_menu(player);
                break;
            case 3:
                system("clear");
                run_supemon_center(player);
                break;
            case 4:
                printf("You left the game. Goodbye!\n");
                return;
            default:
                printf("Erreur : cette option n'existe pas !\n");
                break;
        }
    }
    system("clear");
}
