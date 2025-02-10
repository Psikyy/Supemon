#include <stdio.h>
#include <stdlib.h>
#include "choice.h"
#include "../shop/shop.h"
#include "../../class/supemon/supemon.h"
#include "../../adventure/shop/shop.h"
#include "../../class/player/player.h"
#include "../../adventure/wild/battle.h"

int choice() {
    int choix;
    int é = 130;

    // Initialisation des mouvements pour les Supémons avec stat_boost
    Move scratch = {"Scratch", 5, 0};  // Ajout du stat_boost
    Move growl = {"Growl", 0, -1};     // Ajout du stat_boost (réduit la défense)
    
    // Supémon du joueur
    Move player_moves[] = {scratch, growl};
    Supemon player_supemon;
    initialize_supemon(&player_supemon, "Pikachu", 25, 15, 10, 5, 10, 10, player_moves);
    
    // Supémon ennemi
    Move enemy_moves[] = {scratch, growl};
    Supemon enemy_supemon;
    initialize_supemon(&enemy_supemon, "Supmander", 20, 12, 8, 4, 8, 8, enemy_moves);
    
    // Initialisation du joueur
    Player player;
    initialize_player(&player, "Ash", 1000, 1);

    // Ajouter le Supémon du joueur
    add_supemon(&player, player_supemon);

    printf("+-----------------------------+\n");
    printf("| Where do you want to go?    |\n");
    printf("|\t1 - Into the wild          |\n");
    printf("|\t2 - Into the shop          |\n");
    printf("|\t3 - In the Supémon Center  |\n");
    printf("|\t4 - Leave the Game         |\n");
    printf("+-----------------------------+\n");

    printf("1, 2, 3 or 4: ");

    if (scanf("%d", &choix) != 1) {
        printf("Erreur : entr%ce invalide !\n", é);
        return 0;
    }

    switch (choix) {
        case 1:
            printf("A wild %s appeared!\n", enemy_supemon.name);
            printf("Go, %s!\n", player.selected_supemon->name);
            battle(&enemy_supemon, &player);
            break;
        case 2:
        {
        int shop_choice;
        while (1) {
            printf("\n=== MENU ===\n");
            printf("1 - Acheter un objet\n");
            printf("2 - Vendre un objet\n");
            printf("3 - Quitter\n");
            printf("Votre choix: ");
            scanf("%d", &shop_choice);

            switch (shop_choice) {
                case 1:
                    buy_item(&player);
                    break;
                case 2:
                    if (player.item_count > 0) {
                        printf("Quel objet vendre (0-%d) ? ", player.item_count - 1);
                        int index;
                        scanf("%d", &index);
                        sell_item(&player, index);
                    } else {
                        printf("Aucun objet à vendre !\n");
                    }
                    break;
                case 3:
                    break; // Quitter la boucle du magasin
                default:
                    printf("Choix invalide.\n");
                    break;
            }
            if (shop_choice == 3) break; // Sortir du `while`
        }
    }
    choice();
    break;
        case 3:
        printf("Bienvenue dans le Supémon Center.");
        return 0;
        case 4:
            printf("You left the game. Goodbye!\n");
            return 0;
            break;
        default:
            printf("Erreur : cette option n'existe pas !\n");
            break;
    }

    return choix;
}
