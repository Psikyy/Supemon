#include <stdio.h>
#include <string.h>
#include <math.h>
#include "supemon.h"
#include "../player/player.h"


// void save_game_text(Player *player, const char *filename) {
//     FILE *file = fopen(filename, "w");
//     if (file == NULL) {
//         printf("Erreur lors de l'ouverture du fichier pour sauvegarde.\n");
//         return;
//     }

//     // Sauvegarde des infos du joueur
//     fprintf(file, "%s %d %d\n", player->name, player->supemon_count, player->supcoins);

//     // Sauvegarde des Supémons
//     for (int i = 0; i < player->supemon_count; i++) {
//         Supemon *s = &player->supemons[i];
//         fprintf(file, "%s %d %d %d %d %d %d %d %d %d\n", 
//                 s->name, s->hp, s->attack, s->defense, s->evasion, 
//                 s->accuracy, s->speed, s->level, s->experience, s->max_hp);

//         // Sauvegarde des mouvements
//         for (int j = 0; j < MAX_MOVES; j++) {
//             fprintf(file, "%s %d %d\n", s->moves[j].name, s->moves[j].power, s->moves[j].stat_boost);
//         }
//     }

//     fclose(file);
//     printf("Partie sauvegardée avec succès dans %s !\n", filename);
// }

// /**
//  * Charge les données du joueur depuis un fichier texte
//  */
// void load_game_text(Player *player, const char *filename) {
//     FILE *file = fopen(filename, "r");
//     if (file == NULL) {
//         printf("Aucune sauvegarde trouvée.\n");
//         return;
//     }

//     // Chargement des infos du joueur
//     fscanf(file, "%s %d %d", player->name, &player->supemon_count, &player->supcoins);

//     // Chargement des Supémons
//     for (int i = 0; i < player->supemon_count; i++) {
//         Supemon *s = &player->supemons[i];
//         fscanf(file, "%s %d %d %d %d %d %d %d %d %d", 
//                s->name, &s->hp, &s->attack, &s->defense, &s->evasion, 
//                &s->accuracy, &s->speed, &s->level, &s->experience, &s->max_hp);

//         // Chargement des mouvements
//         for (int j = 0; j < MAX_MOVES; j++) {
//             fscanf(file, "%s %d %d", s->moves[j].name, &s->moves[j].power, &s->moves[j].stat_boost);
//         }
//     }

//     fclose(file);
//     printf("Partie chargée avec succès depuis %s !\n", filename);
// }


void initialize_supemon(Supemon *s, const char *name, int hp, int attack, int defense, int evasion, int accuracy, int speed, Move moves[]) {
    strcpy(s->name, name);
    s->level = 1;
    s->experience = 0;
    s->hp = s->max_hp = hp;
    s->attack = s->base_attack = attack;
    s->defense = s->base_defense = defense;
    s->evasion = s->base_evasion = evasion;
    s->accuracy = s->base_accuracy = accuracy;
    s->speed = speed;
    memcpy(s->moves, moves, sizeof(Move) * MAX_MOVES);
}


int get_exp_for_level(int level) {
    if (level <= 1) return 0;
    return 500 + (level - 2) * 1000;
}

// Fonction utilitaire pour arrondir avec 50% de chance up/down
int random_round(float value) {
    float decimal_part = value - (int)value;
    if (decimal_part == 0) return (int)value;
    
    float random = (float)rand() / RAND_MAX;
    
    return random < 0.5 ? floor(value) : ceil(value);
}

void apply_level_up(Supemon *s) {
    // Augmente toutes les stats de 30% avec arrondissement aléatoire
    float increase_factor = 1.30;
    
    s->max_hp = random_round(s->max_hp * increase_factor);
    s->hp = s->max_hp;  // Restaure les HP au maximum
    
    s->base_attack = random_round(s->base_attack * increase_factor);
    s->attack = s->base_attack;  // Reset des stats actuelles aux nouvelles stats de base
    
    s->base_defense = random_round(s->base_defense * increase_factor);
    s->defense = s->base_defense;
    
    s->base_accuracy = random_round(s->base_accuracy * increase_factor);
    s->accuracy = s->base_accuracy;
    
    s->base_evasion = random_round(s->base_evasion * increase_factor);
    s->evasion = s->base_evasion;
    
    s->speed = random_round(s->speed * increase_factor);
    
    s->level++;
    
    printf("%s reached level %d!\n", s->name, s->level);
    printf("New stats:\n");
    printf("HP: %d\n", s->max_hp);
    printf("Attack: %d\n", s->attack);
    printf("Defense: %d\n", s->defense);
    printf("Accuracy: %d\n", s->accuracy);
    printf("Evasion: %d\n", s->evasion);
    printf("Speed: %d\n", s->speed);
}

void check_level_up(Supemon *s) {
    while (1) {
        // Calcule l'expérience nécessaire pour le prochain niveau
        int exp_needed = get_exp_for_level(s->level + 1);
        
        // Si le Supémon n'a pas assez d'expérience pour le prochain niveau, sort de la boucle
        if (s->experience < exp_needed) {
            break;
        }
        
        // Applique le level up
        apply_level_up(s);
    }
}