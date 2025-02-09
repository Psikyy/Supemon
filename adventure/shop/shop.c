#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../class/player/player.h"
#include "shop.h"

ShopItem shop_items[SHOP_MAX_ITEMS] = {
    {"Potion", 100, 5},         // Soigne 5 HP
    {"Super Potion", 300, 10},  // Soigne 10 HP
    {"Rare Candy", 700, 1}      // Augmente le niveau
};

// Fonction pour nettoyer l'écran
void clear_screen() {
    #ifdef _WIN32
        system("cls");  // Pour Windows
    #endif
}

// Fonction pour afficher les objets dans le shop
void display_shop() {
    clear_screen();  // Nettoyer l'écran à chaque ouverture du shop
    printf("\n=== SHOP ===\n");
    for (int i = 0; i < SHOP_MAX_ITEMS; i++) {
        printf("%d - %s (%d Supcoins)\n", i + 1, shop_items[i].name, shop_items[i].price);
    }
    printf("0 - Quitter le shop\n");
}

// Fonction pour acheter un objet
void buy_item(Player *player) {
    int choice, quantity;
    display_shop();

    printf("\nVotre solde: %d Supcoins\n", player->supcoins);
    printf("Choisissez un objet à acheter (0 pour quitter) : ");
    scanf("%d", &choice);

    if (choice < 1 || choice > SHOP_MAX_ITEMS) {
        printf("Achat annulé.\n");
        return;
    }

    ShopItem selected_item = shop_items[choice - 1];  // Remplacer Item par ShopItem
    // Demander la quantité
    printf("Combien voulez-vous acheter de %s ? : ", selected_item.name);
    scanf("%d", &quantity);

    if (quantity <= 0) {
        printf("Quantité invalide.\n");
        return;
    }

    // Vérification du budget
    int total_price = selected_item.price * quantity;
    if (player->supcoins < total_price) {
        printf("Vous n'avez pas assez de Supcoins !\n");
        return;
    }

    // Ajout de l’objet dans l’inventaire
    if (player->item_count + quantity <= MAX_ITEMS) {
        for (int i = 0; i < quantity; i++) {
            strcpy(player->items[player->item_count].name, selected_item.name);
            player->items[player->item_count].effect = selected_item.effect;
            player->item_count++;
        }
        player->supcoins -= total_price;
        printf("Vous avez acheté %d x %s !\n", quantity, selected_item.name);
    } else {
        printf("Inventaire plein !\n");
    }
}

// Fonction pour vendre un objet
void sell_item(Player *player, int item_index) {
    if (item_index < 0 || item_index >= player->item_count) {
        printf(":x: Objet invalide !\n");
        return;
    }

    Item *item = &player->items[item_index];  // Pas de changement ici car 'Item' reste utilisé dans player.h
    int original_price = 0;

    // Trouver le prix de l'objet en se basant sur le shop
    for (int i = 0; i < SHOP_MAX_ITEMS; i++) {
        if (strcmp(shop_items[i].name, item->name) == 0) {
            original_price = shop_items[i].price;  // On récupère le prix original
            break;
        }
    }

    if (original_price == 0) {
        printf(":warning: Prix inconnu, annulation de la vente.\n");
        return;
    }

    int selling_price = original_price / 2;  // Calcul du prix de vente

    printf(":moneybag: Prix original: %d, Prix vente: %d\n", original_price, selling_price); // Debug

    player->supcoins += selling_price;  // Ajoute les Supcoins au joueur

    // Supprime l'objet en décalant les autres
    for (int i = item_index; i < player->item_count - 1; i++) {
        player->items[i] = player->items[i + 1];
    }
    player->item_count--;

    printf(":white_check_mark: Vous avez vendu %s pour %d Supcoins.\n", item->name, selling_price);
}

void use_item(Player *player, int item_index) {
    if (item_index < 0 || item_index >= player->item_count) {
        printf("Indice invalide !\n");
        return;
    }

    if (player->selected_supemon == NULL) {
        printf("Aucun Supémon sélectionné !\n");
        return;
    }

    Item item = player->items[item_index];

    if (strcmp(item.name, "Potion") == 0 || strcmp(item.name, "Super Potion") == 0) {
        if (player->selected_supemon->hp < player->selected_supemon->max_hp) {
            player->selected_supemon->hp += item.effect;
            if (player->selected_supemon->hp > player->selected_supemon->max_hp) {
                player->selected_supemon->hp = player->selected_supemon->max_hp;
            }
            printf("%s a utilisé %s ! PV restaurés à %d.\n", player->selected_supemon->name, item.name, player->selected_supemon->hp);
        } else {
            printf("Les PV sont déjà au maximum !\n");
            return;
        }
    } else if (strcmp(item.name, "Rare Candy") == 0) {
        player->selected_supemon->level++;
        printf("%s a gagné un niveau ! Il est maintenant niveau %d !\n", player->selected_supemon->name, player->selected_supemon->level);
    }

    // Supprimer l'objet après usage
    for (int i = item_index; i < player->item_count - 1; i++) {
        player->items[i] = player->items[i + 1];
    }
    player->item_count--;
}