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

bool Player::craft(const crafting::Recipe& recipe, unsigned int variation) {
    auto it = crafting::recipeMap.find(recipe);
    if(it == crafting::recipeMap.end()) {
        return false;
    }
    std::vector<std::shared_ptr<crafting::Character>> results = it->second;
    if(variation >= results.size()) {
        return false;
    }
    if(!inventory.removeIngredients(recipe)) {
        return false;
    }
    inventory.addItem(results[variation]->getCharacter());
    return true;
}



} // namespace player