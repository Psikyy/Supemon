#include "Supemon.h"

void initialize_supemon(Supemon *s, const char *name, int hp, int attack, int defense, int evasion, int accuracy, int speed, Move moves[]) {
    strcpy(s->name, name);
    s->level = 1;
    s->experience = 0;
    s->max_hp = hp;
    s->hp = hp;
    s->base_attack = s->attack = attack;
    s->base_defense = s->defense = defense;
    s->base_evasion = s->evasion = evasion;
    s->base_accuracy = s->accuracy = accuracy;
    s->speed = speed;
    for (int i = 0; i < MAX_MOVES; i++) {
        s->moves[i] = moves[i];
    }
}