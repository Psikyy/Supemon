#include <stdio.h>
#include <string.h>
#include <math.h>
#include "supemon.h"
#include "../player/player.h"

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
    int old_level = s->level;
    s->level++;
    float increase_factor = 1.30;
    
    // Sauvegarder les anciennes stats pour montrer l'évolution
    int old_hp = s->max_hp;
    int old_attack = s->attack;
    int old_defense = s->defense;
    int old_accuracy = s->accuracy;
    int old_evasion = s->evasion;
    int old_speed = s->speed;
    
    // Calcul des nouvelles stats
    s->max_hp = random_round(s->max_hp * increase_factor);
    s->hp = s->max_hp;
    s->attack = random_round(s->attack * increase_factor);
    s->base_attack = s->attack;
    s->defense = random_round(s->defense * increase_factor);
    s->base_defense = s->defense;
    s->accuracy = random_round(s->accuracy * increase_factor);
    s->base_accuracy = s->accuracy;
    s->evasion = random_round(s->evasion * increase_factor);
    s->base_evasion = s->evasion;
    s->speed = random_round(s->speed * increase_factor);
    
    printf("\n╔═══════════════════════════════════════╗\n");
    printf("║         ÉVOLUTION DES STATS           ║\n");
    printf("╠═══════════════════════════════════════╣\n");
    printf("║ %s est passé au niveau %d!\n", s->name, s->level);
    printf("║\n");
    printf("║ HP:       %d → %d (+%d)\n", old_hp, s->max_hp, s->max_hp - old_hp);
    printf("║ Attaque:  %d → %d (+%d)\n", old_attack, s->attack, s->attack - old_attack);
    printf("║ Défense:  %d → %d (+%d)\n", old_defense, s->defense, s->defense - old_defense);
    printf("║ Précision:%d → %d (+%d)\n", old_accuracy, s->accuracy, s->accuracy - old_accuracy);
    printf("║ Esquive:  %d → %d (+%d)\n", old_evasion, s->evasion, s->evasion - old_evasion);
    printf("║ Vitesse:  %d → %d (+%d)\n", old_speed, s->speed, s->speed - old_speed);
    printf("╚═══════════════════════════════════════╝\n");
}

void check_level_up(Supemon *s) {
    while (1) {
        int exp_needed = get_exp_for_level(s->level + 1);
        
        printf("\n╔════════════════════════════════════╗\n");
        printf("║           STATUT NIVEAU            ║\n");
        printf("╠════════════════════════════════════╣\n");
        printf("║ %s - Niveau %d\n", s->name, s->level);
        printf("║ XP: %d / %d\n", s->experience, exp_needed);
        printf("║ XP restante: %d\n", exp_needed - s->experience);
        printf("╚════════════════════════════════════╝\n");
        
        if (s->experience < exp_needed) {
            break;
        }
        
        printf("\n⭐ NIVEAU SUPÉRIEUR! ⭐\n");
        apply_level_up(s);
    }
}