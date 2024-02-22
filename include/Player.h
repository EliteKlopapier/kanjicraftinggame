
#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "Recipe.h"
#include <memory>
#include <map>

namespace player {

struct ItemStack {
    // The item in the stack.
    std::shared_ptr<crafting::Character> item;
    // The amount of the item in the stack.
    unsigned int amount;

    bool operator<(const ItemStack& other) const {
        return item->getCharacter() < other.item->getCharacter();
    }
};

/**
 * @brief The Player class represents a player in the game.
*/
class Player {
private:
    // The player's health.
    unsigned int mHealth;
    // The player's maximum health.
    unsigned int mMaxHealth;
    // The player's gold, resource used for trading.
    unsigned int mGold;
    // The player's ink, resource used for crafting.
    unsigned int mInk;
    // The player's maximum ink.
    unsigned int mMaxInk;
    // The player's inventory as a map that attributes an item's amount to each character in the inventory.
    std::map<char32_t, unsigned int> inventory;
public:
    /**
     * @brief Constructs a player with the given health, maximum health, gold and ink.
    */
    Player(unsigned int health = 10, unsigned int maxHealth = 10, unsigned int gold = 0, unsigned int ink = 0, unsigned int maxInk = 10);

    /**
     * @brief Gets the player's health.
     * @return The player's health.
    */
    unsigned int getHealth() const { return mHealth; }

    /**
     * @brief Gets the player's maximum health.
     * @return The player's maximum health.
    */
    unsigned int getMaxHealth() const { return mMaxHealth; }

    /**
     * @brief Gets the player's amount of gold.
     * @return The player's gold.
    */
    unsigned int getGold() const { return mGold; }

    /**
     * @brief Gets the player's amount of ink.
     * @return The player's ink.
    */
    unsigned int getInk() const { return mInk; }

    /**
     * @brief Gets the player's maximum ink.
     * @return The player's maximum ink.
    */

    unsigned int getMaxInk() const { return mMaxInk; }

    /**
     * @brief Gets the player's inventory.
     * @return The player's inventory.
    */
    std::map<char32_t, unsigned int> getInventory() const { return inventory; }

    /**
     * @brief Sets the player's health.
     * @param health The player's new health.
    */
    void setHealth(unsigned int health) { mHealth = health; }

    /**
     * @brief Sets the player's maximum health.
     * @param maxHealth The player's new maximum health.
    */
    void setMaxHealth(unsigned int maxHealth) { mMaxHealth = maxHealth; }

    /**
     * @brief Sets the player's gold.
     * @param gold The player's new amount of gold.
    */
    void setGold(unsigned int gold) { mGold = gold; }

    /**
     * @brief Sets the player's ink.
     * @param ink The player's new amount of ink.
    */
    void setInk(unsigned int ink) { mInk = ink; }

    /**
     * @brief Sets the player's maximum ink.
     * @param maxInk The player's new maximum ink.
    */
    void setMaxInk(unsigned int maxInk) { mMaxInk = maxInk; }

    /**
     * @brief Adds an item to the player's inventory.
     * @param item The item to add.
     * @param amount The amount of the item to add.
    */
    void addItem(char32_t item, unsigned int amount = 1);

    /**
     * @brief Removes an item from the player's inventory.
     * @param item The item to remove.
     * @param amount The amount of the item to remove, or all if negative.
    */
    void removeItem(char32_t item, int amount = -1);

    /**
     * @brief Clears the player's inventory.
    */
    void clearInventory();

    /**
     * @brief Checks if the player has the given amount of the given item in their inventory.
     * @param item The item to check for.
     * @param amount The amount of the item to check for.
     * @return True if the player has the item, false otherwise.
    */  
    bool hasItem(char32_t item, unsigned int amount = 1) const;

    /**
     * @brief Checks if the player has the given ingredient or the components thereof in their inventory.
     * @param ingredient The ingredient to check for.
     * @return True if the player has the ingredient, false otherwise.
    */
    bool hasIngredients(const crafting::Ingredient& ingredient) const;

    /**
     * @brief Removes the given ingredients from the player's inventory.
     * @param ingredient The ingredients to remove.
     * @return True if the ingredients were successfully removed, false otherwise.
    */
    bool removeIngredients(const crafting::Ingredient& ingredient);

    /**
     * @brief Crafts the given recipe from the items in the player's inventory, if available.
     * @param recipe The recipe to craft.
     * @param variation The index of the item to craft, if the recipe has multiple possible results.
     * @return True if the recipe was successfully crafted, false otherwise.
    */
    bool craft(const crafting::Recipe& recipe, unsigned int variation = 0);

};

} // namespace player

#endif // PLAYER_H
