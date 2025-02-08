#include <stdio.h>
#include "class/player/player.h"
#include "adventure/shop/shop.h"

int main() {
    Player player;
    initialize_player(&player, "Ash", 1000, 1);

    int choix;
    while (1) {
        printf("\n=== MENU ===\n");
        printf("1 - Acheter un objet\n");
        printf("2 - Vendre un objet\n");
        printf("3 - Quitter\n");
        printf("Votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                buy_item(&player);
                break;
            case 2:
                sell_item(&player, 0);
                break;
            case 3:
                printf("Au revoir !\n");
                return 0;
            default:
                printf("Choix invalide !\n");
        }
    }
}
