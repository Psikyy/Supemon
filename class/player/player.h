#ifndef PLAYER_H
#define PLAYER_H

#include "../supemon/supemon.h"

#define MAX_SUPEMONS 6
#define MAX_ITEMS 10

typedef struct {
    char name[20];
    int price;
    int effect;
} Item;

typedef struct {
    char name[50];
    int supcoins;
    int supemon_count;
    Supemon supemons[MAX_SUPEMONS];
    Supemon *selected_supemon;
    int item_count;
    Item items[MAX_ITEMS];  // ✅ Assure-toi que c'est bien un tableau de Item
} Player;


void initialize_player(Player *p, const char *name, int supcoins, int starter_choice);
void add_supemon(Player *p, Supemon s);

#endif
