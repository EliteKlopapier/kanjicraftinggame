#include "Character.h"

namespace crafting {

Character::Character(char32_t character) : mCharacter(character) {}

bool Character::operator==(const Ingredient& other) const {
    const Character* otherCharacter = dynamic_cast<const Character*>(&other);
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

bool Character::operator==(const Character& other) const {
    if(mCharacter == other.getCharacter()) {
        return true;
    }
    else {
        return false;
    }
}

Character::operator std::u32string() const {
    return std::u32string(1, mCharacter);
}

rendering::Bitmap Character::render(int width, int height) const {
    if(FT_Get_Char_Index(rendering::fontFace, mCharacter) == 0 && !recipes.empty()) {
        // if the character is not in the font, use the first recipe to render it
        return recipes[0].render(width, height);
    }
    if(FT_Set_Pixel_Sizes(rendering::fontFace, width, height)) {
        throw std::runtime_error("Failed to set pixel sizes for font face.");
    }
    if(FT_Load_Char(rendering::fontFace, mCharacter, FT_LOAD_RENDER)) {
        throw std::runtime_error("(1) Failed to load character " + std::to_string(mCharacter));
    }
    FT_Bitmap bitmap;
    if(rendering::fontFace->glyph->bitmap.width != 0) {
        bitmap = rendering::fontFace->glyph->bitmap;
    }
    else {
        throw std::runtime_error("(2) Failed to load character " + std::to_string(mCharacter));
    }
    return rendering::Bitmap(bitmap).placeOnCanvas(width, height);
}

void Character::addRecipe(std::u32string recipeString) {
    const char32_t* firstChar = recipeString.c_str();	
    recipes.emplace_back(Recipe(recipeString));
}

} // namespace crafting