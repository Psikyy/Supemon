#ifndef PLAYER_H
#define PLAYER_H

#include "Supemon.h"

#define MAX_SUPEMONS 6
#define MAX_ITEMS 10

typedef struct {
    char name[MAX_NAME_LENGTH];
    Supemon supemons[MAX_SUPEMONS];
    int supemon_count;
    Supemon *selected_supemon;
    int supcoins;
    char items[MAX_ITEMS][MAX_NAME_LENGTH];
    int item_count;
} Player;

void initialize_player(Player *p, const char *name, int supcoins);
void add_supemon(Player *p, Supemon s);

#endif