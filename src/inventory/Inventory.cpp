#include "Inventory.h"
#include "Recipe.h"
#include "Character.h"

namespace inventory {


bool Inventory::addItem(char32_t item, unsigned int amount) {
    if(getTotalAmount() + amount > capacity && capacity != 0) {
        return false;
    }
    items[item] += amount;
    return true;
}

void Inventory::removeItem(char32_t item, int amount) {
    if(items.find(item) != items.end()) {
        if(amount < 0 || items[item] <= amount) {
            items.erase(item);
        }
        else {
            items[item] -= amount;
        }
    }
}

void Inventory::clearInventory() {
    items.clear();
}

bool Inventory::hasItem(char32_t item, unsigned int amount) const {
    auto it = items.find(item);
    return it != items.end() && it->second >= amount;
}

bool Inventory::hasIngredients(const crafting::Ingredient& ingredient) const {
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

bool Inventory::removeIngredients(const crafting::Ingredient& ingredient) {
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

unsigned int Inventory::getTotalAmount() const {
    unsigned int total = 0;
    for(const auto& item : items) {
        total += item.second;
    }
    return total;
}

} // namespace inventory