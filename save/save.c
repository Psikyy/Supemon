#include "save.h"
#include <stdio.h>
#include <stdlib.h>

int save_game(Player *player, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier de sauvegarde\n");
        return 0;
    }

    // Sauvegarde des données basiques du joueur
    fwrite(player->name, sizeof(char), MAX_NAME_LENGTH, file);
    fwrite(&player->supemon_count, sizeof(int), 1, file);
    fwrite(&player->supcoins, sizeof(int), 1, file);
    fwrite(&player->item_count, sizeof(int), 1, file);

    // Sauvegarde de l'index du Supémon sélectionné
    int selected_index = -1;
    for (int i = 0; i < player->supemon_count; i++) {
        if (&player->supemons[i] == player->selected_supemon) {
            selected_index = i;
            break;
        }
    }
    fwrite(&selected_index, sizeof(int), 1, file);

    // Sauvegarde des Supémons
    for (int i = 0; i < player->supemon_count; i++) {
        Supemon *s = &player->supemons[i];
        fwrite(s->name, sizeof(char), MAX_NAME_LENGTH, file);
        fwrite(&s->level, sizeof(int), 1, file);
        fwrite(&s->experience, sizeof(int), 1, file);
        fwrite(&s->hp, sizeof(int), 1, file);
        fwrite(&s->max_hp, sizeof(int), 1, file);
        fwrite(&s->attack, sizeof(int), 1, file);
        fwrite(&s->base_attack, sizeof(int), 1, file);
        fwrite(&s->defense, sizeof(int), 1, file);
        fwrite(&s->base_defense, sizeof(int), 1, file);
        fwrite(&s->evasion, sizeof(int), 1, file);
        fwrite(&s->base_evasion, sizeof(int), 1, file);
        fwrite(&s->accuracy, sizeof(int), 1, file);
        fwrite(&s->base_accuracy, sizeof(int), 1, file);
        fwrite(&s->speed, sizeof(int), 1, file);
        
        // Sauvegarde des moves
        for (int j = 0; j < MAX_MOVES; j++) {
            fwrite(s->moves[j].name, sizeof(char), 50, file);
            fwrite(&s->moves[j].damage, sizeof(int), 1, file);
            fwrite(&s->moves[j].stat_boost, sizeof(int), 1, file);
        }
    }

    // Sauvegarde des items
    for (int i = 0; i < player->item_count; i++) {
        fwrite(player->items[i].name, sizeof(char), 20, file);
        fwrite(&player->items[i].price, sizeof(int), 1, file);
        fwrite(&player->items[i].effect, sizeof(int), 1, file);
    }

    fclose(file);
    return 1;
}

Player* load_game(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Fichier de sauvegarde non trouvé\n");
        return NULL;
    }

    Player *player = (Player*)malloc(sizeof(Player));
    
    // Lecture des données basiques du joueur
    fread(player->name, sizeof(char), MAX_NAME_LENGTH, file);
    fread(&player->supemon_count, sizeof(int), 1, file);
    fread(&player->supcoins, sizeof(int), 1, file);
    fread(&player->item_count, sizeof(int), 1, file);

    // Allouer la mémoire pour les items
    player->items = (Item*)malloc(sizeof(Item) * MAX_ITEMS);

    // Lecture de l'index du Supémon sélectionné
    int selected_index;
    fread(&selected_index, sizeof(int), 1, file);

    // Lecture des Supémons
    for (int i = 0; i < player->supemon_count; i++) {
        Supemon *s = &player->supemons[i];
        fread(s->name, sizeof(char), MAX_NAME_LENGTH, file);
        fread(&s->level, sizeof(int), 1, file);
        fread(&s->experience, sizeof(int), 1, file);
        fread(&s->hp, sizeof(int), 1, file);
        fread(&s->max_hp, sizeof(int), 1, file);
        fread(&s->attack, sizeof(int), 1, file);
        fread(&s->base_attack, sizeof(int), 1, file);
        fread(&s->defense, sizeof(int), 1, file);
        fread(&s->base_defense, sizeof(int), 1, file);
        fread(&s->evasion, sizeof(int), 1, file);
        fread(&s->base_evasion, sizeof(int), 1, file);
        fread(&s->accuracy, sizeof(int), 1, file);
        fread(&s->base_accuracy, sizeof(int), 1, file);
        fread(&s->speed, sizeof(int), 1, file);

        // Lecture des moves
        for (int j = 0; j < MAX_MOVES; j++) {
            fread(s->moves[j].name, sizeof(char), 50, file);
            fread(&s->moves[j].damage, sizeof(int), 1, file);
            fread(&s->moves[j].stat_boost, sizeof(int), 1, file);
        }
    }

    // Définir le Supémon sélectionné
    if (selected_index >= 0 && selected_index < player->supemon_count) {
        player->selected_supemon = &player->supemons[selected_index];
    } else {
        player->selected_supemon = NULL;
    }

    // Lecture des items
    for (int i = 0; i < player->item_count; i++) {
        fread(player->items[i].name, sizeof(char), 20, file);
        fread(&player->items[i].price, sizeof(int), 1, file);
        fread(&player->items[i].effect, sizeof(int), 1, file);
    }

    fclose(file);
    return player;
}