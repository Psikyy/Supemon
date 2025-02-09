#ifndef BATTLE_H
#define BATTLE_H
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../../class/supemon/supemon.h"
#include "../../class/player/player.h"

// Fonction pour effectuer une attaque
void perform_attack(Supemon *attacker, Supemon *defender, int move_index);

// Fonction pour gérer l'utilisation d'un objet par le joueur
void handle_use_item(Player *player);

// Fonction principale pour gérer le combat
void battle(Supemon *enemy_supemon, Player *player);

// Prototypes des fonctions manquantes
int display_battle_screen(Supemon *enemy_supemon, Player *player);
void handle_move(Supemon *enemy_supemon, Player *player);
void handle_change_supemon(Player *player);
void handle_capture(Supemon *enemy_supemon, Player *player);
bool handle_run_away(Supemon *enemy_supemon, Player *player);

#endif // BATTLE_H
