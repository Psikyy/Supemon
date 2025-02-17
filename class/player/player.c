#include <stdio.h>
#include <string.h>
#include "player.h"
#include "../supemon/supemon.h"

void initialize_player(Player *p, const char *name, int supcoins, int starter_choice) {
    memset(p, 0, sizeof(Player));  // Initialise toute la structure à 0
    p->item_count = 0;  // Initialise l'inventaire à 0 items

    if (!p) {
    printf("Erreur : joueur non initialisé !\n");
    return;
    }

    if (p->items != NULL) {
        return;
    }


    p->items = malloc(MAX_ITEMS * sizeof(Item));

    if (!p->items) {
        printf("Erreur d'allocation mémoire pour l'inventaire !\n");
        exit(1);
    }
    for (int i = 0; i < MAX_ITEMS; i++) {
    p->items[i].name[0] = '\0';  // Vide la chaîne pour éviter les accès mémoire invalides
    p->items[i].effect = 0;      // Initialise `effect`
    }

    strcpy(p->name, name);
    p->supemon_count = 0;
    p->selected_supemon = NULL;
    p->supcoins = supcoins;

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

    if (p->supemon_count >= MAX_SUPEMONS) {
    printf("Erreur : impossible d'ajouter un Supémon !\n");
    return;
    }

    p->supemons[p->supemon_count++] = starter; // Ajoute correctement le starter
    p->selected_supemon = &p->supemons[0];  // Assurez-vous que le premier Supémon sélectionné est correct
}


// N'oublie pas de libérer la mémoire allouée pour p->items quand tu as fini avec le joueur
void free_player(Player *p) {
    if (p->items) {
        free(p->items);
        p->items = NULL;
    }
}

void add_supemon(Player *p, Supemon s) {
    if (p->supemon_count < MAX_SUPEMONS) {
        p->supemons[p->supemon_count++] = s;
        if (p->selected_supemon == NULL) {
            p->selected_supemon = &p->supemons[0];
        }
    }
}