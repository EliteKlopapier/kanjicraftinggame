
#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "Recipe.h"
#include "Inventory.h"
#include "Modifier.h"
#include <memory>
#include <map>
#include <vector>

namespace player {

/**
 * @brief The Player class represents a player in the game.
*/
class Player {
private:
    // The player's health.
    unsigned int mHealth;
    // The player's gold, resource used for trading.
    unsigned int mGold;
    // The player's ink, resource used for crafting.
    unsigned int mInk;
    // The player's inventory.
    inventory::Inventory inventory;
    // The player's modifiers.
    std::vector<Modifier> modifiers;
    /**
     * @brief Gets the value of the given stat, taking into account the modifiers.^
     * @param stat The stat to get.
     * @param min The minimum value of the stat.
    */
    int getStat(Stats stat, int min) const;
public:
    /**
     * @brief Constructs a player with the given health, maximum health, gold and ink.
    */
    Player(unsigned int maxHealth = 10, unsigned int maxInk = 10, unsigned int health = 10, unsigned int gold = 0, unsigned int ink = 5);

    /**
     * @brief Gets the player's health.
     * @return The player's health.
    */
    unsigned int getHealth() const { return mHealth; }

    /**
     * @brief Gets the player's maximum health.
     * @return The player's maximum health.
    */
    unsigned int getMaxHealth() const;

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

    unsigned int getMaxInk() const;

    /**
     * @brief Gets the player's armor.
     * @return The player's armor.
    */
    unsigned int getArmor() const;

    /**
     * @brief Gets the player's inventory.
     * @return The player's inventory.
    */
    inventory::Inventory& getInventory() { return inventory; }

    /**
     * @brief Sets the player's health.
     * @param health The player's new health.
    */
    void setHealth(unsigned int health) { mHealth = health; }

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
     * @brief Changes the player's health by the given amount.
    */
    void changeHealth(int amount);

    /**
     * @brief Changes the player's gold by the given amount.
    */
    void changeGold(int amount);

    /**
     * @brief Changes the player's ink by the given amount.
    */
    void changeInk(int amount);

    /**
     * @brief Adds a modifier to the player.
     * @param name The name or source of the modifier.
     * @param stat The stat that the modifier affects.
     * @param value The value by which the stat is modified.
     * @return A pointer to the added modifier.
    */
    Modifier* addModifier(const std::string& name, Stats stat, int value);

    /**
     * @brief Adds a modifier to the player.
     * @param modifier The modifier to add.
     * @return A pointer to the added modifier.
    */
    Modifier* addModifier(const Modifier& modifier);

    /**
     * @brief Removes a modifier from the player.
     * @param modifierPtr A pointer to the modifier to remove.
     * @return True if the modifier was successfully removed, false otherwise.
    */
    bool removeModifier(Modifier* modifierPtr);

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
