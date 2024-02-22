#include "Player.h"
#include "hashMaps.h"

namespace player {

Player::Player(unsigned int health, unsigned int maxHealth, unsigned int gold, unsigned int ink, unsigned int maxInk)
    : mHealth(health)
    , mMaxHealth(maxHealth)
    , mGold(gold)
    , mInk(ink)
    , mMaxInk(maxInk)
    , inventory()
{ }

void Player::addItem(char32_t item, unsigned int amount) {
    inventory[item] += amount;
}

void Player::removeItem(char32_t item, int amount) {
    if(inventory.find(item) != inventory.end()) {
        if(amount < 0 || inventory[item] <= amount) {
            inventory.erase(item);
        }
        else {
            inventory[item] -= amount;
        }
    }
}

void Player::clearInventory() {
    inventory.clear();
}

bool Player::hasItem(char32_t item, unsigned int amount) const {
    auto it = inventory.find(item);
    return it != inventory.end() && it->second >= amount;
}

bool Player::hasIngredients(const crafting::Ingredient& ingredient) const {
    const crafting::Character* character_cast = dynamic_cast<const crafting::Character*>(&ingredient);
    if(character_cast) {
        return hasItem(character_cast->getCharacter());
    }
    const crafting::Recipe* recipe_cast = dynamic_cast<const crafting::Recipe*>(&ingredient);
    if(recipe_cast) {
        for(const auto& subIngredient : recipe_cast->getIngredients()) {
            if(!hasIngredients(*subIngredient.get())) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool Player::removeIngredients(const crafting::Ingredient& ingredient) {
    if(!hasIngredients(ingredient)) {
        return false;
    }
    const crafting::Character* character_cast = dynamic_cast<const crafting::Character*>(&ingredient);
    if(character_cast) {
        removeItem(character_cast->getCharacter());
        return true;
    }
    const crafting::Recipe* recipe_cast = dynamic_cast<const crafting::Recipe*>(&ingredient);
    if(recipe_cast) {
        for(const auto& subIngredient : recipe_cast->getIngredients()) {
            if(!removeIngredients(*subIngredient.get())) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool Player::craft(const crafting::Recipe& recipe, unsigned int variation) {
    auto it = crafting::recipeMap.find(recipe);
    if(it == crafting::recipeMap.end()) {
        return false;
    }
    std::vector<std::shared_ptr<crafting::Character>> results = it->second;
    if(variation >= results.size()) {
        return false;
    }
    if(!removeIngredients(recipe)) {
        return false;
    }
    addItem(results[variation]->getCharacter());
    return true;
}



} // namespace player