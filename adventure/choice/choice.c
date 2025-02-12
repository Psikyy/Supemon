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
        printf("|\t1 - Into the wild          |\n");
        printf("|\t2 - Into the shop          |\n");
        printf("|\t3 - In the Supémon Center  |\n");
        printf("|\t4 - Leave the Game         |\n");
        printf("+-----------------------------+\n");

        print_inventory(player);

        printf("1, 2, 3 or 4: ");
        if (scanf("%d", &choix) != 1) {
            printf("Erreur : entrée invalide !\n");
            return;
        }

        switch (choix) {
            case 1:
                Supemon wild_supemon = get_random_wild_supemon();
                battle(&wild_supemon, player);
                break;
            case 2:
                buy_item(player);
                break;
            case 3:
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
}
