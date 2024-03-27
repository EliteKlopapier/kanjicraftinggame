#include "EmptyIngredient.h"
#include "Character.h"

namespace crafting {

bool EmptyIngredient::operator==(const Ingredient& other) const {
    try {
        dynamic_cast<const EmptyIngredient&>(other);
        return true;
    }
    catch(std::bad_cast& e) {
        return false;
    }
}

EmptyIngredient::operator std::u32string() const {
    return std::u32string();
}

rendering::GreyBitmap EmptyIngredient::render(int width, int height) const {
    return rendering::GreyBitmap(width, height);
}

std::shared_ptr<Ingredient> EmptyIngredient::addLeft(std::shared_ptr<Character> character) {
    return character;
}

std::shared_ptr<Ingredient> EmptyIngredient::addRight(std::shared_ptr<Character> character) {
    return character;
}

std::shared_ptr<Ingredient> EmptyIngredient::addAbove(std::shared_ptr<Character> character) {
    return character;
}

std::shared_ptr<Ingredient> EmptyIngredient::addBelow(std::shared_ptr<Character> character) {
    return character;
}

} // namespace crafting