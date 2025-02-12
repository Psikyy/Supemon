// player.h
#ifndef PLAYER_H
#define PLAYER_H

#include "../supemon/supemon.h"

#define MAX_SUPEMONS 6
#define MAX_ITEMS 10
#define MAX_NAME_LENGTH 50

typedef struct
{
    char name[20];
    int price;
    int effect;
}Item ;


typedef struct {
    char name[MAX_NAME_LENGTH];
    Supemon supemons[MAX_SUPEMONS];
    int supemon_count;
    Supemon *selected_supemon;
    int supcoins;
    Item *items;  // Pointeur pour allouer dynamiquement
    int item_count;
} Player;

// Ajout du paramètre starter_choice
void initialize_player(Player *p, const char *name, int supcoins, int starter_choice);

void add_supemon(Player *p, Supemon s);

void free_player(Player *p);
void save_player(const Player *player, const char *filename);
void load_player(Player *player, const char *filename);


#endif // PLAYER_H
