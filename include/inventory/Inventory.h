#ifndef INVENTORY_H
#define INVENTORY_H

#include "Ingredient.h"
#include <map>

namespace inventory {
    
class Inventory {
private:
    // The inventory as a map that attributes an item's amount to each character in the inventory.
    std::map<char32_t, unsigned int> items;
    // The maximum capacity of the inventory. Unlimited if 0.
    unsigned int capacity;
public:
    /**
     * @brief Constructs an inventory with the given capacity.
     * @param capacity The maximum capacity of the inventory.
    */
    Inventory(unsigned int capacity = 0) : capacity(capacity) {}

    /**
     * @brief Adds an item to the inventory.
     * @param item The item to add.
     * @param amount The amount of the item to add.
     * @return True if the item was successfully added, false otherwise.
    */
    bool addItem(char32_t item, unsigned int amount = 1);

    /**
     * @brief Removes an item from the inventory.
     * @param item The item to remove.
     * @param amount The amount of the item to remove, or all if negative.
    */
    void removeItem(char32_t item, int amount = -1);

    /**
     * @brief Clears the inventory.
    */
    void clearInventory();

    /**
     * @brief Checks if the inventory contains the given amount of the given item.
     * @param item The item to check for.
     * @param amount The amount of the item to check for.
     * @return True if the player has the item, false otherwise.
    */  
    bool hasItem(char32_t item, unsigned int amount = 1) const;

    /**
     * @brief Checks if the inventory contains the given ingredient or the components thereof.
     * @param ingredient The ingredient to check for.
     * @return True if the player has the ingredient, false otherwise.
    */
    bool hasIngredients(const crafting::Ingredient& ingredient) const;

    /**
     * @brief Removes the given ingredients from the inventory.
     * @param ingredient The ingredients to remove.
     * @return True if the ingredients were successfully removed, false otherwise.
    */
    bool removeIngredients(const crafting::Ingredient& ingredient);

    /**
     * @brief Gets the total amount of items in the inventory.
    */
    unsigned int getTotalAmount() const;
};

} // namespace inventory

#endif // INVENTORY_H
