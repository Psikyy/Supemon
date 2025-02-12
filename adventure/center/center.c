#include <stdio.h>
#include "center.h"
#include "../../class/player/player.h"

void display_center_welcome() {
    printf("+---------------------------------------------+\n");
    printf("|    Welcome to the Supémon Center!           |\n");
    printf("|We'll heal your Supémons to perfect health!  |\n");
    printf("+---------------------------------------------+\n");
}

void heal_all_supemons(Player *player) {
    for (int i = 0; i < player->supemon_count; i++) {
        // Restaure les HP au maximum
        player->supemons[i].hp = player->supemons[i].max_hp;
        
        printf("%s has been fully healed!\n", player->supemons[i].name);
    }
}

void display_player_supemons(Player *player) {
    printf("\nYour Supémons:\n");
    printf("+-----------------------------------+\n");
    for (int i = 0; i < player->supemon_count; i++) {
        Supemon *s = &player->supemons[i];
        printf("|%d. %s (Level %d)\n              |", i + 1, s->name, s->level);
        printf("|   HP: %d/%d\n                    |", s->hp, s->max_hp);
        printf("+---------------------------------+\n");
    }
}

void run_supemon_center(Player *player) {
    char choice;
    
    display_center_welcome();
    display_player_supemons(player);
    
    printf("\nWould you like to heal all your Supémons? (y/n): ");
    scanf(" %c", &choice);
    
    if (choice == 'y' || choice == 'Y') {
        printf("+-------------------------------------------------------+\n");
        printf("|Okay! Let me take care of your Supémons!               |\n");
        printf("...\n");
        heal_all_supemons(player);
        printf("|All your Supémons have been healed to perfect health!  |\n");
        printf("|We hope to see you again!\n");
        printf("+-------------------------------------------------------+\n");
    } else {
        printf("|Okay! We hope to see you again!                        |\n");
        printf("+-------------------------------------------------------+\n");
    }
    system("clear");
}