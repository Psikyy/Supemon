#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "class/supemon/supemon.h"
#include "adventure/shop/shop.h"
#include "class/player/player.h"
#include "adventure/wild/battle.h"

int main() {
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

    int choix;
    while (1) {
        printf("\n=== MENU ===\n");
        printf("1 - Acheter un objet\n");
        printf("2 - Vendre un objet\n");
        printf("3 - Combattre\n");
        printf("4 - Utiliser un objet\n");
        printf("5 - Quitter\n");
        printf("Votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
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
                printf("A wild %s appeared!\n", enemy_supemon.name);
                printf("Go, %s!\n", player.selected_supemon->name);
                battle(&enemy_supemon, &player);
                break;
            case 4:
                if (player.item_count > 0) {
                    printf("Inventaire :\n");
                    for (int i = 0; i < player.item_count; i++) {
                        printf("%d - %s\n", i, player.items[i].name);
                    }
                    printf("Quel objet utiliser (0-%d) ? ", player.item_count - 1);
                    int index;
                    scanf("%d", &index);
                    use_item(&player, index);
                } else {
                    printf("Aucun objet à utiliser !\n");
                }
                break;
            case 5:
                printf("Au revoir !\n");
                return 0;
            default:
                printf("Choix invalide !\n");
        }
    }
        
        return 0;
    }