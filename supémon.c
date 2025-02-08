#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "class/supemon/supemon.h"
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
    initialize_player(&player, "Ash", 100);
    
    // Ajouter le Supémon du joueur
    add_supemon(&player, player_supemon);
    
    // Affichage initial
    printf("A wild %s appeared!\n", enemy_supemon.name);
    printf("Go, %s!\n", player.selected_supemon->name);
    
    // Démarrer le combat
    battle(&enemy_supemon, &player);
    
    return 0;
}