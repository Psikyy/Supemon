#ifndef SAVE_SYSTEM_H
#define SAVE_SYSTEM_H

#include "../class//player/player.h"

// Sauvegarde la partie dans un fichier
// Retourne 1 si succès, 0 si échec
int save_game(Player *player, const char *filename);

// Charge une partie depuis un fichier
// Retourne un pointeur vers Player si succès, NULL si échec
Player* load_game(const char *filename);

#endif