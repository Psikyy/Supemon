#include <stdio.h>
#include <string.h>
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