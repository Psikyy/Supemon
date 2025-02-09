#ifndef SUPEMON_H
#define SUPEMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_MOVES 2

typedef struct {
    char name[50];
    int damage;
    int stat_boost;  // Ajout du champ stat_boost
} Move;


typedef struct {
    char name[MAX_NAME_LENGTH];
    int level;
    int experience;
    int hp, max_hp;
    int attack, base_attack;
    int defense, base_defense;
    int evasion, base_evasion;
    int accuracy, base_accuracy;
    int speed;
    Move moves[MAX_MOVES];
} Supemon;

void initialize_supemon(Supemon *s, const char *name, int hp, int attack, int defense, int evasion, int accuracy, int speed, Move moves[]);

#endif