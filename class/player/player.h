// player.h
#ifndef PLAYER_H
#define PLAYER_H

#include "Supemon.h"

#define MAX_SUPEMONS 6
#define MAX_ITEMS 20
#define MAX_NAME_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];
    Supemon supemons[MAX_SUPEMONS];
    int supemon_count;
    Supemon *selected_supemon;
    int supcoins;
    int items[MAX_ITEMS];
    int item_count;
} Player;

// Ajout du paramètre starter_choice
void initialize_player(Player *p, const char *name, int supcoins, int starter_choice);

void add_supemon(Player *p, Supemon s);

#endif // PLAYER_H
