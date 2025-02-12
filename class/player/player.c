#include <stdio.h>
#include <string.h>
#include "player.h"
#include "../supemon/supemon.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "player.h"

void save_player(const Player *player, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Erreur : Impossible d'ouvrir le fichier de sauvegarde !\n");
        return;
    }
    
    // Sauvegarde des informations du joueur
    fprintf(file, "Nom: %s\n", player->name);
    fprintf(file, "Supcoins: %d\n", player->supcoins);
    fprintf(file, "Nombre de Supémons: %d\n", player->supemon_count);
    
    // Sauvegarde des Supémons
    for (int i = 0; i < player->supemon_count; i++) {
        fprintf(file, "Supémon %d: %s\n", i + 1, player->supemons[i].name);
        fprintf(file, "  - HP: %d\n", player->supemons[i].hp);
        fprintf(file, "  - Attack: %d\n", player->supemons[i].attack);
        fprintf(file, "  - Defense: %d\n", player->supemons[i].defense);
    }
    
    // Sauvegarde des objets
    fprintf(file, "Nombre d'objets: %d\n", player->item_count);
    for (int i = 0; i < player->item_count; i++) {
        fprintf(file, "Objet %d: %s (Effet: %d, Prix: %d)\n", 
                i + 1, player->items[i].name, player->items[i].effect, player->items[i].price);
    }
    
    fclose(file);
    printf("Sauvegarde réussie dans %s !\n", filename);
}

void load_player(Player *player, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Aucune sauvegarde trouvée. Démarrage d'une nouvelle partie.\n");
        return;
    }
    
    fscanf(file, "Nom: %s\n", player->name);
    fscanf(file, "Supcoins: %d\n", &player->supcoins);
    fscanf(file, "Nombre de Supémons: %d\n", &player->supemon_count);
    
    for (int i = 0; i < player->supemon_count; i++) {
        fscanf(file, "Supémon %d: %s\n", &i, player->supemons[i].name);
        fscanf(file, "  - HP: %d\n", &player->supemons[i].hp);
        fscanf(file, "  - Attack: %d\n", &player->supemons[i].attack);
        fscanf(file, "  - Defense: %d\n", &player->supemons[i].defense);
    }
    
    fscanf(file, "Nombre d'objets: %d\n", &player->item_count);
    for (int i = 0; i < player->item_count; i++) {
        fscanf(file, "Objet %d: %s (Effet: %d, Prix: %d)\n", 
               &i, player->items[i].name, &player->items[i].effect, &player->items[i].price);
    }
    
    fclose(file);
    printf("Chargement réussi depuis %s !\n", filename);
}

void initialize_player(Player *p, const char *name, int supcoins, int starter_choice) {
    if (p->items != NULL) {
        return;
    }

    p->items = malloc(MAX_ITEMS * sizeof(Item));
    if (!p->items) {
        printf("Erreur d'allocation mémoire pour l'inventaire !\n");
        exit(1);
    }

    strcpy(p->name, name);
    p->supemon_count = 0;
    p->selected_supemon = NULL;
    p->supcoins = supcoins;
    p->item_count = 0;

    Supemon starter;

    switch (starter_choice) {
        case 1:
            initialize_supemon(&starter, "Supmander", 10, 1, 1, 1, 2, 1, (Move[]) {
                {"Scratch", 3, 0},
                {"Growl", 0, 1}
            });
            break;
        case 2:
            initialize_supemon(&starter, "Supasaur", 9, 1, 1, 3, 2, 2, (Move[]) {
                {"Vine Whip", 3, 0},
                {"Leer", 0, 1}
            });
            break;
        case 3:
            initialize_supemon(&starter, "Supirtle", 11, 1, 2, 2, 1, 2, (Move[]) {
                {"Water Gun", 3, 0},
                {"Tail Whip", 0, 1}
            });
            break;
        default:
            printf("Choix invalide pour le Supémon de départ.\n");
            return;
    }

    p->supemons[p->supemon_count++] = starter; // Ajoute correctement le starter
    p->selected_supemon = &p->supemons[0];  // Assurez-vous que le premier Supémon sélectionné est correct

    // Initialisation de l'inventaire
    for (int i = 0; i < MAX_ITEMS; i++) {
        p->items[i].name[0] = '\0';
        p->items[i].effect = 0;
    }
}


// N'oublie pas de libérer la mémoire allouée pour p->items quand tu as fini avec le joueur
void free_player(Player *p) {
    free(p->items);
}


void add_supemon(Player *p, Supemon s) {
    if (p->supemon_count < MAX_SUPEMONS) {
        p->supemons[p->supemon_count++] = s;
        if (p->selected_supemon == NULL) {
            p->selected_supemon = &p->supemons[0];
        }
    }
}