#include "Player.h"
#include "hashMaps.h"

namespace player {

Player::Player(unsigned int maxHealth, unsigned int maxInk, unsigned int health, unsigned int gold, unsigned int ink)
    : mHealth(health)
    , mGold(gold)
    , mInk(ink)
    , inventory()
    , modifiers{
        { "Base", Stats::MAX_HEALTH, (int)maxHealth },
        { "Base", Stats::MAX_INK, (int)maxInk }
    }
{ }

unsigned int Player::getMaxHealth() const {
    int maxHealth = 0;
    for(const auto& modifier : modifiers) {
        if(modifier.stat == Stats::MAX_HEALTH) {
            maxHealth += modifier.value;
        }
    }
    return maxHealth > 0 ? maxHealth : 1;
}

unsigned int Player::getMaxInk() const {
    int maxInk = 0;
    for(const auto& modifier : modifiers) {
        if(modifier.stat == Stats::MAX_INK) {
            maxInk += modifier.value;
        }
    }
    return maxInk > 0 ? maxInk : 1;
}

unsigned int Player::getArmor() const {
    int armor = 0;
    for(const auto& modifier : modifiers) {
        if(modifier.stat == Stats::ARMOR) {
            armor += modifier.value;
        }
    }
    return armor >= 0 ? armor : 0;
}

Modifier* Player::addModifier(const std::string& name, Stats stat, int value) {
    modifiers.emplace_back(name, stat, value);
    return &modifiers.back();
}

Modifier* Player::addModifier(const Modifier& modifier) {
    modifiers.push_back(modifier);
    return &modifiers.back();
}

bool Player::removeModifier(Modifier* modifierPtr) {
    for(auto it = modifiers.begin(); it != modifiers.end(); ++it) {
        if(&(*it) == modifierPtr) {
            modifiers.erase(it);
            return true;
        }
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
    if(!inventory.removeIngredients(recipe)) {
        return false;
    }
    inventory.addItem(results[variation]->getCharacter());
    return true;
}



} // namespace player