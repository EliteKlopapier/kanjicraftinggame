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

int Player::getStat(Stats stat, int min) const {
    int value = min;
    for(const auto& modifier : modifiers) {
        if(modifier.getStat() == stat) {
            value += modifier.getValue();
        }
    }
    return value >= min ? value : min;
}

unsigned int Player::getMaxHealth() const {
    return getStat(Stats::MAX_HEALTH, 1);
}

unsigned int Player::getMaxInk() const {
    return getStat(Stats::MAX_INK, 1);
}

unsigned int Player::getArmor() const {
    return getStat(Stats::ARMOR, 0);
}

void Player::changeHealth(int amount) {
    mHealth += amount;
    if(mHealth < 0) {
        mHealth = 0;
    }
    if(mHealth > getMaxHealth()) {
        mHealth = getMaxHealth();
    }
}

void Player::changeGold(int amount) {
    mGold += amount;
    if(mGold < 0) {
        mGold = 0;
    }
}

void Player::changeInk(int amount) {
    mInk += amount;
    if(mInk < 0) {
        mInk = 0;
    }
    if(mInk > getMaxInk()) {
        mInk = getMaxInk();
    }
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