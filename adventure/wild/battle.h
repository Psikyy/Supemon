#ifndef BATTLE_H
#define BATTLE_H
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../../class/supemon/supemon.h"
#include "../../class/player/player.h"

// Fonction pour effectuer une attaque
void perform_attack(Supemon *attacker, Supemon *defender, int move_index);

// Fonction pour calculer le taux de capture d'un Supémon
double calculate_capture_rate(int max_hp, int current_hp);

// Fonction pour calculer le taux d'évasion
double calculate_escape_rate(int player_speed, int enemy_speed);

// Fonction pour gérer le choix de mouvement du joueur
void handle_move(Supemon *enemy_supemon, Player *player);

// Fonction pour gérer le changement de Supémon du joueur
void handle_change_supemon(Player *player);

// Fonction pour gérer l'utilisation d'un objet par le joueur
void handle_use_item(Player *player);

// Fonction pour gérer la capture d'un Supémon
void handle_capture(Supemon *enemy_supemon, Player *player);

// Fonction pour gérer la fuite du joueur
bool handle_run_away(Supemon *enemy_supemon, Player *player);

// Fonction pour afficher l'écran de bataille
int display_battle_screen(Supemon *enemy_supemon, Player *player);

// Fonction principale pour gérer le combat
void battle(Supemon *enemy_supemon, Player *player);

#endif // BATTLE_H
