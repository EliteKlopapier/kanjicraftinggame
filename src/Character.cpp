#include "Character.h"

namespace crafting {

Character::Character(char32_t character) : mCharacter(character) {}

bool Character::operator==(Ingredient& other) {
    Character* otherCharacter = dynamic_cast<Character*>(&other);
    if(otherCharacter == nullptr) {
        return false;
    }
    else if(mCharacter == otherCharacter->getCharacter()) {
        return true;
    }
    else {
        return false;
    }
}

bool Character::operator==(Character& other) {
    if(mCharacter == other.getCharacter()) {
        return true;
    }
    else {
        return false;
    }
}

Character::operator std::u32string() {
    return std::u32string(1, mCharacter);
}

void Character::addRecipe(std::u32string recipeString) {
    const char32_t* firstChar = recipeString.c_str();	
    recipes.emplace_back(Recipe(recipeString));
}

} // namespace crafting