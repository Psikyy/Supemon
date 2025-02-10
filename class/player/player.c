#include <stdio.h>
#include <string.h>
#include "player.h"
#include "../supemon/supemon.h"

void initialize_player(Player *p, const char *name, int supcoins, int starter_choice) {
    if (p->items != NULL) {
        return;  // Si les items sont déjà initialisés, ne réalloue pas
    }

    // Allocation dynamique pour items
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

    // Initialisation des moves vides
    Move empty_moves[MAX_MOVES] = {
        { "", 0, 0 },  // Nom, damage, stat_boost
        { "", 0, 0 }
    };

    // Choisir le Supémon de départ
    Supemon starter;
    switch (starter_choice) {
        case 1:
            initialize_supemon(&starter, "Supmander", 10, 1, 1, 1, 2, 1, empty_moves); break;
        case 2:
            initialize_supemon(&starter, "Supasaur", 9, 1, 1, 3, 2, 2, empty_moves); break;
        case 3:
            initialize_supemon(&starter, "Supirtle", 11, 1, 2, 2, 1, 2, empty_moves); break;
        default:
            printf("Choix invalide pour le Supémon de départ.\n");
            return;
    }
    p->supemons[0] = starter; // Affecte le Supémon au joueur

    // Initialisation de l'inventaire (données dans p->items)
    for (int i = 0; i < MAX_ITEMS; i++) {
        p->items[i].name[0] = '\0';  // Assure que les noms sont vides
        p->items[i].effect = 0;      // Initialise l'effet à 0
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