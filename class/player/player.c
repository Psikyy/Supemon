#include <stdio.h>
#include <string.h>
#include "player.h"
#include "../supemon/supemon.h"

void initialize_player(Player *p, const char *name, int supcoins, int starter_choice) {
    strcpy(p->name, name);
    p->supcoins = supcoins;
    p->supemon_count = 1; // Un Supémon au départ
    p->item_count = 0;
    p->selected_supemon = &p->supemons[0]; // On pointe vers le premier Supémon

    // Initialisation des mouvements
    Move empty_moves[MAX_MOVES] = { { "", 0, 0, "" }, { "", 0, 0, "" } };

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
}

void add_supemon(Player *p, Supemon s) {
    if (p->supemon_count < MAX_SUPEMONS) {
        p->supemons[p->supemon_count++] = s;
    }
}
