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
    FT_Face fontFace;
    if(FT_Get_Char_Index(rendering::fontFaceMain, mCharacter) != 0) {
        fontFace = rendering::fontFaceMain;
    }
    else if(FT_Get_Char_Index(rendering::fontFaceBackUp1, mCharacter) != 0) {
        fontFace = rendering::fontFaceBackUp1;
    }
    else if(FT_Get_Char_Index(rendering::fontFaceBackUp2, mCharacter) != 0) {
        fontFace = rendering::fontFaceBackUp2;
    }
    else if(!recipes.empty()) {
        // If the character is not in any of the font faces, use the first recipe to render it.
        return recipes[0].render(width, height);
    }
    else {
        throw std::runtime_error("Character " + std::to_string(mCharacter) + " can not be rendered because it is not in any of the font faces and has no recipes.");
    }
    
    if(FT_Set_Pixel_Sizes(fontFace, width, height)) {
        throw std::runtime_error("Failed to set pixel sizes for font face.");
    }
    if(FT_Load_Char(fontFace, mCharacter, FT_LOAD_RENDER)) {
        throw std::runtime_error("(1) Failed to load character " + std::to_string(mCharacter));
    }
    FT_Bitmap bitmap;
    if(fontFace->glyph->bitmap.width != 0) {
        bitmap = fontFace->glyph->bitmap;
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