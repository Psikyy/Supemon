#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../../class/supemon/supemon.h"
#include "../../class/player/player.h"

void perform_attack(Supemon *attacker, Supemon *defender, int move_index) {
    if (move_index < 0 || move_index >= MAX_MOVES) {
        printf("Invalid move index.\n");
        return;
    }

    Move move = attacker->moves[move_index];
    int damage = 0;

    if (strcmp(move.name, "Scratch") == 0) {
        damage = attacker->attack - defender->defense;
        if (damage < 0) damage = 0;
        defender->hp -= damage;
        printf("%s used Scratch!\n", attacker->name);
        printf("It dealt %d damage to %s!\n", damage, defender->name);
    }
    else if (strcmp(move.name, "Growl") == 0) {
        printf("%s used Growl!\n", attacker->name);
        printf("%s's defense decreased!\n", defender->name);
        defender->defense -= 1;
    }
    else {
        printf("%s used %s!\n", attacker->name, move.name);
        printf("Move not implemented or unsupported.\n");
    }
    
    if (defender->hp <= 0) {
        printf("%s fainted!\n", defender->name);
        defender->hp = 0;
    }
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
    
    // Affichage des mouvements disponibles pour le Supémon du joueur
    for (int i = 0; i < MAX_MOVES; i++) {
        if (strlen(player->selected_supemon->moves[i].name) > 0) {
            printf("%d - %s\n", i + 1, player->selected_supemon->moves[i].name);
        }
    }

    printf("Choose move (1-%d): ", MAX_MOVES);
    int move_choice;
    scanf("%d", &move_choice);

    if (move_choice >= 1 && move_choice <= MAX_MOVES) {
        // Appel de perform_attack avec le mouvement choisi
        perform_attack(player->selected_supemon, enemy_supemon, move_choice - 1);

        // Contre-attaque de l'ennemi s'il est encore en vie
        if (enemy_supemon->hp > 0) {
            int enemy_move = rand() % MAX_MOVES;  // Choisir aléatoirement un mouvement de l'ennemi
            perform_attack(enemy_supemon, player->selected_supemon, enemy_move);
        }
    } else {
        printf("Invalid choice!\n");
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

void handle_use_item(Player *player) {
    if (player->item_count == 0) {
        printf("No items in inventory!\n");
        return;
    }
    
    printf("\nAvailable items:\n");
    for (int i = 0; i < player->item_count; i++) {
        printf("%d - %s\n", i + 1, player->items[i].name);
    }
    
    int choice;
    printf("Choose an item to use (1-%d): ", player->item_count);
    scanf("%d", &choice);
    
    if (choice < 1 || choice > player->item_count) {
        printf("Invalid choice!\n");
        return;
    }
    
    Item selected_item = player->items[choice - 1];
    
    if (strcmp(selected_item.name, "Potion") == 0) {
        player->selected_supemon->hp += 5;
        if (player->selected_supemon->hp > player->selected_supemon->max_hp)
            player->selected_supemon->hp = player->selected_supemon->max_hp;
        printf("%s's HP restored by 5!\n", player->selected_supemon->name);
    } else if (strcmp(selected_item.name, "Super Potion") == 0) {
        player->selected_supemon->hp += 10;
        if (player->selected_supemon->hp > player->selected_supemon->max_hp)
            player->selected_supemon->hp = player->selected_supemon->max_hp;
        printf("%s's HP restored by 10!\n", player->selected_supemon->name);
    } else if (strcmp(selected_item.name, "Rare Candy") == 0) {
        player->selected_supemon->level += 1;
        printf("%s leveled up to %d!\n", player->selected_supemon->name, player->selected_supemon->level);
    } else {
        printf("This item cannot be used in battle!\n");
        return;
    }
    
    for (int i = choice - 1; i < player->item_count - 1; i++) {
        player->items[i] = player->items[i + 1];
    }
    player->item_count--;
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
}

void calculate_exp_gain(Supemon *winner, Supemon *loser) {
    // Formule de base pour le gain d'XP :
    // (Niveau du perdant * 50) + bonus si le niveau du perdant est plus élevé
    int base_exp = loser->level * 50;

    // Bonus si le Supémon vaincu est d'un niveau plus élevé
    if (loser->level > winner->level) {
        base_exp = base_exp * 1.5; // 50% bonus
    }

    printf("%s gained %d experience points!\n", winner->name, base_exp);
    winner->experience += base_exp;
    check_level_up(winner);
}

void battle(Supemon *enemy_supemon, Player *player) {
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
                handle_use_item(player);
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
                printf("Invalid choice!\n");
                break;
        }
        
        if (enemy_supemon->hp <= 0) {
            printf("%s fainted!\n", enemy_supemon->name);
            calculate_exp_gain(player->selected_supemon, enemy_supemon);
            battle_ended = true;
        }
        if (player->selected_supemon->hp <= 0) {
            printf("%s fainted!\n", player->selected_supemon->name);
        }
    }
}