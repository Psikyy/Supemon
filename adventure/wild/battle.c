#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../../class/supemon/supemon.h"
#include "../../class/player/player.h"
#include <unistd.h>
#include "../../adventure/shop/shop.h"

Supemon get_random_wild_supemon() {
    Supemon wild_supemons[3];

    // Supmander
    initialize_supemon(&wild_supemons[0], "Supmander", 10, 1, 1, 1, 2, 1, (Move[]) {
        {"Scratch", 3, 0},
        {"Growl", 0, 1}
    });

    // Supasaur
    initialize_supemon(&wild_supemons[1], "Supasaur", 9, 1, 1, 3, 2, 2, (Move[]) {
        {"Vine Whip", 3, 0},
        {"Leer", 0, 1}
    });

    // Supirtle
    initialize_supemon(&wild_supemons[2], "Supirtle", 11, 1, 2, 2, 1, 2, (Move[]) {
        {"Water Gun", 3, 0},
        {"Tail Whip", 0, 1}
    });

    int random_index = rand() % 3;
    printf("Created wild Supemon: %s with HP: %d\n", wild_supemons[random_index].name, wild_supemons[random_index].hp);
    return wild_supemons[random_index];
}

void perform_attack(Supemon *attacker, Supemon *defender, int move_index) {
    if (move_index < 0 || move_index >= MAX_MOVES) {
        printf("Invalid move index.\n");
        return;
    }

    Move move = attacker->moves[move_index];
    int damage = 0;

    // Attaques offensives
    if (move.damage > 0) {
        damage = move.damage + attacker->attack - defender->defense;
        if (damage < 1) damage = 1;  // Minimum 1 dégât
        defender->hp -= damage;
        printf("%s used %s!\n", attacker->name, move.name);
        printf("It dealt %d damage to %s!\n", damage, defender->name);
    }
    // Attaques de statut
    else if (move.stat_boost > 0) {
        // Pour Growl, Tail Whip et Leer
    if (strcmp(move.name, "Growl") == 0 || strcmp(move.name, "Tail Whip") == 0 || strcmp(move.name, "Leer") == 0) {
        printf("%s used %s!\n", attacker->name, move.name);
        if (defender->defense > 0) {
            defender->defense -= 1;
            printf("%s's defense decreased to %d!\n", defender->name, defender->defense);
        } else {
            printf("%s's defense can't go any lower!\n", defender->name);
        }
    }
        else if (strcmp(move.name, "Foliage") == 0) {
            printf("%s used %s!\n", attacker->name, move.name);
            printf("%s's evasion increased!\n", attacker->name);
            attacker->evasion += 1;
        }
    }
    
    if (defender->hp <= 0) {
        printf("%s fainted!\n", defender->name);
        defender->hp = 0;
    }
}

void calculate_exp_gain(Supemon *winner, Supemon *loser) {
    int exp_multiplier = (rand() % 401) + 100; // Random between 100 and 500
    int base_exp = loser->level * exp_multiplier;
    printf("%s gained %d experience points!\n", winner->name, base_exp);
    winner->experience += base_exp;
    check_level_up(winner);
}

double calculate_capture_rate(int max_hp, int current_hp) {
    double rate = ((double)(max_hp - current_hp) / max_hp) - 0.5;
    return rate < 0 ? 0 : rate;  // On s'assure que le taux ne soit jamais négatif
}

double calculate_escape_rate(int player_speed, int enemy_speed) {
    if (player_speed + enemy_speed == 0) {
        return 0;  // Éviter la division par zéro
    }
    return (double)player_speed / (player_speed + enemy_speed);
}


void handle_move(Supemon *enemy_supemon, Player *player) {
    printf("\nAvailable Moves:\n");

    // Affichage des mouvements du joueur
    for (int i = 0; i < MAX_MOVES; i++) {
        if (strlen(player->selected_supemon->moves[i].name) > 0) {
            printf("%d - %s\n", i + 1, player->selected_supemon->moves[i].name);
        }
    }

    printf("Choose move (1-%d): ", MAX_MOVES);
    int move_choice;
    scanf("%d", &move_choice);

    if (move_choice >= 1 && move_choice <= MAX_MOVES) {
        int enemy_move = rand() % MAX_MOVES; // Mouvement aléatoire pour l'ennemi
        
        // Déterminer qui attaque en premier basé sur la vitesse
        Supemon *first_attacker, *second_attacker;
        int first_move, second_move;
        
        if (player->selected_supemon->speed > enemy_supemon->speed) {
            // Le joueur est plus rapide
            first_attacker = player->selected_supemon;
            second_attacker = enemy_supemon;
            first_move = move_choice - 1;
            second_move = enemy_move;
            printf("\n%s est plus rapide et attaque en premier!\n", player->selected_supemon->name);
        }
        else if (enemy_supemon->speed > player->selected_supemon->speed) {
            // L'ennemi est plus rapide
            first_attacker = enemy_supemon;
            second_attacker = player->selected_supemon;
            first_move = enemy_move;
            second_move = move_choice - 1;
            printf("\n%s est plus rapide et attaque en premier!\n", enemy_supemon->name);
        }
        else {
            // Même vitesse, choix aléatoire
            if (rand() % 2 == 0) {
                first_attacker = player->selected_supemon;
                second_attacker = enemy_supemon;
                first_move = move_choice - 1;
                second_move = enemy_move;
                printf("\nÉgalité de vitesse! %s attaque en premier!\n", player->selected_supemon->name);
            } else {
                first_attacker = enemy_supemon;
                second_attacker = player->selected_supemon;
                first_move = enemy_move;
                second_move = move_choice - 1;
                printf("\nÉgalité de vitesse! %s attaque en premier!\n", enemy_supemon->name);
            }
        }
        
        // Exécuter les attaques dans l'ordre
        perform_attack(first_attacker, second_attacker, first_move);
        
        // Vérifier si le second attaquant peut encore attaquer
        if (second_attacker->hp > 0) {
            perform_attack(second_attacker, first_attacker, second_move);
        }
        
    } else {
        printf("Invalid move choice!\n");
    }
}

void handle_change_supemon(Player *player) {
    printf("\nAvailable Supémons:\n");
    for (int i = 0; i < player->supemon_count; i++) {
        printf("%d - %s (HP: %d/%d)\n", 
               i + 1, 
               player->supemons[i].name, 
               player->supemons[i].hp, 
               player->supemons[i].max_hp);
    }
    
    int choice;
    printf("Choose Supémon (1-%d): ", player->supemon_count);
    scanf("%d", &choice);
    
    if (choice >= 1 && choice <= player->supemon_count) {
        player->selected_supemon = &player->supemons[choice - 1];
        printf("Go, %s!\n", player->selected_supemon->name);
    }
}

void handle_victory(Player *player, Supemon *enemy_supemon) {
    int supcoins_reward = (rand() % 401) + 100; // Random between 100 and 500
    player->supcoins += supcoins_reward;
    printf("You won the battle! You earned %d Supcoins!\n", supcoins_reward);
    calculate_exp_gain(player->selected_supemon, enemy_supemon);
}

void handle_capture(Supemon *enemy_supemon, Player *player) {
    double capture_rate = calculate_capture_rate(enemy_supemon->max_hp, enemy_supemon->hp);
    float random = (float)rand() / RAND_MAX;
    
    if (random < capture_rate) {
        add_supemon(player, *enemy_supemon);
        printf("Successfully captured %s!\n", enemy_supemon->name);
        // Mettre fin au combat
    } else {
        printf("Failed to capture %s!\n", enemy_supemon->name);
    }
}

bool handle_run_away(Supemon *enemy_supemon, Player *player) {
    double escape_rate = calculate_escape_rate(
        player->selected_supemon->speed, 
        enemy_supemon->speed
    );
    float random = (float)rand() / RAND_MAX;
    
    if (random < escape_rate) {
        printf("Got away safely!\n");
        return true;
    } else {
        printf("Couldn't escape!\n");
        return false;
    }
    return false;
}

int display_battle_screen(Supemon *enemy_supemon, Player *player) {
    printf("Your turn...\n\n");
    
    // Affichage du Supémon ennemi
    printf("%s (enemy)\n", enemy_supemon->name);
    printf("--------------------------------\n");
    printf("HP: %d/%d        Lvl: %d\n", 
           enemy_supemon->hp, 
           enemy_supemon->max_hp, 
           enemy_supemon->level);
    printf("Atk: %d          Def: %d\n", 
           enemy_supemon->attack, 
           enemy_supemon->defense);
    printf("Acc: %d          Eva: %d\n", 
           enemy_supemon->accuracy, 
           enemy_supemon->evasion);
    printf("--------------------------------\n");
    
    // Affichage du Supémon du joueur
    printf("%s (%s)\n", 
           player->selected_supemon->name, 
           player->name);
    printf("HP: %d/%d        Lvl: %d\n", 
           player->selected_supemon->hp, 
           player->selected_supemon->max_hp, 
           player->selected_supemon->level);
    printf("Atk: %d          Def: %d\n", 
           player->selected_supemon->attack, 
           player->selected_supemon->defense);
    printf("Acc: %d          Eva: %d\n", 
           player->selected_supemon->accuracy, 
           player->selected_supemon->evasion);
    printf("--------------------------------\n");
    
    // Menu principal
    printf("+--------------------------------+\n");
    printf("|What will you do?               |\n");
    printf("|1 - Move                        |\n");
    printf("|2 - Change Supémon             |\n");
    printf("|3 - Use item                    |\n");
    printf("|4 - Capture                     |\n");
    printf("|5 - Run away                    |\n");
    printf("+--------------------------------+\n");
    int choix;
    printf("1, 2, 3, 4 or 5: ");
    scanf("%d", &choix); 
    return choix;
    system("clear");
}

void battle(Supemon *enemy_supemon, Player *player) {
    if (enemy_supemon == NULL || player == NULL) {
        printf("Error: Invalid enemy or player.\n");
        return;
    }

    printf("A wild %s appears!\n", enemy_supemon->name);
    printf("Go %s!\n", player->selected_supemon->name);
    
    int choix;
    bool battle_ended = false;
    
    while (!battle_ended && enemy_supemon->hp > 0 && player->selected_supemon->hp > 0) {
        choix = display_battle_screen(enemy_supemon, player);
        
        switch (choix) {
            case 1:
                handle_move(enemy_supemon, player);
                break;
            case 2:
                handle_change_supemon(player);
                break;
            case 3:
                // The item index is the choice from the menu (adjusted to 0-based index)
                if (player->item_count > 0) {
                    int item_choice;
                    printf("Choose an item to use (1-%d): ", player->item_count);
                    scanf("%d", &item_choice);
                    if (item_choice >= 1 && item_choice <= player->item_count) {
                        use_item(player, item_choice - 1); // Call the use_item function with the correct index
                    } else {
                        printf("Invalid item choice!\n");
                    }
                } else {
                    printf("No items in inventory!\n");
                }
                break;
            case 4:
                handle_capture(enemy_supemon, player);
                battle_ended = true;
                break;
            case 5:
                if (handle_run_away(enemy_supemon, player)) {
                    battle_ended = true;
                }
                break;
            default:
                printf("Invalid choice! Please enter a number between 1 and 5.\n");
                break;
        }
        usleep(5000000); // Pause de 2 secondes
        system("clear");
        
        if (enemy_supemon->hp <= 0) {
            printf("%s fainted!\n", enemy_supemon->name);
            handle_victory(player, enemy_supemon);
            battle_ended = true;
        }
        if (player->selected_supemon->hp <= 0) {
            printf("%s fainted!\n", player->selected_supemon->name);
            printf("You lost the battle... No reward this time.\n");
            battle_ended = true;
        }
    }
}