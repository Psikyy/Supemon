#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../class/player/player.h"
#include "shop.h"

ShopItem shop_items[SHOP_MAX_ITEMS] = {
    {"Potion", 100, 5},
    {"Super Potion", 300, 10},
    {"Rare Candy", 700, 1}
};

void display_shop() {
    system("clear");
    printf("+------------------------------------------------------------+\n");
    printf("|                          SHOP                             |\n");
    printf("+------------------------------------------------------------+\n");
    for (int i = 0; i < SHOP_MAX_ITEMS; i++) {
        printf("| %d - %-15s (%3d Supcoins) ", i + 1, shop_items[i].name, shop_items[i].price);
        if ((i + 1) % 2 == 0 || i == SHOP_MAX_ITEMS - 1) printf("|\n");
    }
    printf("| 0 - Retour                                                 |\n");
    printf("+------------------------------------------------------------+\n");
}

void buy_item(Player *player) {
    int choice, quantity;
    display_shop();
    printf("\nVotre solde: %d Supcoins\n", player->supcoins);
    printf("Choisissez un objet à acheter (0 pour quitter) : ");
    scanf("%d", &choice);
    while (getchar() != '\n');
    if (choice < 1 || choice > SHOP_MAX_ITEMS) {
        system("clear");
        return;
    }
    
    ShopItem selected_item = shop_items[choice - 1];
    printf("Combien voulez-vous acheter de %s ? : ", selected_item.name);
    scanf("%d", &quantity);
    while (getchar() != '\n');
    if (quantity <= 0) return;
    
    int total_price = selected_item.price * quantity;
    if (player->supcoins < total_price) {
        printf("Fonds insuffisants !\n");
        return;
    }
    if (player->item_count + quantity > MAX_ITEMS) {
        printf("Inventaire plein !\n");
        return;
    }
    
    for (int i = 0; i < quantity; i++) {
        strcpy(player->items[player->item_count].name, selected_item.name);
        player->items[player->item_count].effect = selected_item.effect;
        player->item_count++;
    }
    player->supcoins -= total_price;
    system("clear");
    printf("Vous avez acheté %d x %s !\n", quantity, selected_item.name);
}

void sell_item(Player *player) {
    system("clear");
    if (player->item_count == 0) {
        printf("\nVous n'avez aucun objet à vendre !\n");
        return;
    }
    printf("\n=== INVENTAIRE ===\n");
    for (int i = 0; i < player->item_count; i++) {
        printf("%d - %s\n", i + 1, player->items[i].name);
    }
    printf("0 - Retour\n");
    
    int choice;
    printf("Choisissez un objet à vendre : ");
    scanf("%d", &choice);
    while (getchar() != '\n');
    if (choice < 1 || choice > player->item_count) {
        system("clear");
        return;
    }
    
    Item *item = &player->items[choice - 1];
    int selling_price = 0;
    for (int i = 0; i < SHOP_MAX_ITEMS; i++) {
        if (strcmp(shop_items[i].name, item->name) == 0) {
            selling_price = shop_items[i].price / 2;
            break;
        }
    }
    
    player->supcoins += selling_price;
    for (int i = choice - 1; i < player->item_count - 1; i++) {
        player->items[i] = player->items[i + 1];
    }
    player->item_count--;
    system("clear");
    printf("Vous avez vendu %s pour %d Supcoins.\n", item->name, selling_price);
}

void shop_menu(Player *player) {
    system("clear");
    int choice;
    while (1) {
        printf("\n+-----------------------------+\n");
        printf("|        SHOP MENU           |\n");
        printf("+-----------------------------+\n");
        printf("| 1 - Acheter                |\n");
        if (player->item_count > 0) {
            printf("| 2 - Vendre                 |\n");
        } else {
            printf("| 2 - Vendre (Indisponible)   |\n");
        }
        printf("| 0 - Quitter                |\n");
        printf("+-----------------------------+\n");
        printf("Votre choix : ");
        scanf("%d", &choice);
        while (getchar() != '\n');
        
        switch (choice) {
            case 1:
                buy_item(player);
                break;
            case 2:
                if (player->item_count > 0) {
                    sell_item(player);
                } else {
                    printf("Vous n'avez aucun objet à vendre !\n");
                }
                break;
            case 0:
                system("clear");
                return;
            default:
                printf("Choix invalide !\n");
        }
    }
}

void use_item(Player *player, int item_index) {
    if (item_index < 0 || item_index >= player->item_count) {
        printf("Objet invalide.\n");
        return;
    }

    Item *item = &player->items[item_index];

    // Gestion des Potions pour augmenter les HP
    if (strcmp(item->name, "Potion") == 0 || strcmp(item->name, "Super Potion") == 0) {
        if (player->selected_supemon->hp == player->selected_supemon->max_hp) {
            printf("Les HP de %s sont déjà au maximum !\n", player->selected_supemon->name);
            return;
        }

        // Augmente les HP du Supémon sans dépasser les HP max
        player->selected_supemon->hp += item->effect;
        if (player->selected_supemon->hp > player->selected_supemon->max_hp) {
            player->selected_supemon->hp = player->selected_supemon->max_hp;
        }

        printf("%s a utilisé %s ! Les HP de %s sont maintenant à %d.\n",
               player->name, item->name, player->selected_supemon->name, player->selected_supemon->hp);
        
        // Retirer l'objet de l'inventaire
        for (int i = item_index; i < player->item_count - 1; i++) {
            player->items[i] = player->items[i + 1];
        }
        player->item_count--;
    } else if (strcmp(item->name, "Rare Candy") == 0) {
        printf("%s", item->name);
        printf("%s a utilisé un Rare Candy !\n", player->selected_supemon->name);
        
        // Au lieu de manipuler l'expérience, on appelle directement apply_level_up
        apply_level_up(player->selected_supemon);

        // Retirer l'objet de l'inventaire
        for (int i = item_index; i < player->item_count - 1; i++) {
            player->items[i] = player->items[i + 1];
        }
        player->item_count--;
    }

    // Si ce n'est ni une Potion, ni un Rare Candy
    else {
        printf("Cet objet n'a pas d'effet connu.\n");
    }
}