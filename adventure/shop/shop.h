#ifndef SHOP_H
#define SHOP_H

#include "../../class/player/player.h"  // Inclure player.h pour accéder à Player

#define SHOP_MAX_ITEMS 3  // Définit clairement le nombre d'objets du shop

typedef struct {
    char name[20];
    int price;
    int effect; // Peut être un effet de soin ou autre
} ShopItem;  // Renommer Item en ShopItem

// Liste des objets disponibles dans le shop
extern ShopItem shop_items[SHOP_MAX_ITEMS];

// Fonctions du Shop
void display_shop();
void buy_item(Player *player);
void sell_item(Player *player, int item_index);
void use_item(Player *player, int item_index);

#endif