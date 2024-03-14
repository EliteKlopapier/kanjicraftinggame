#include "Character.h"
#include "byteUtil.h"
#include "hashMaps.h"

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

bool Character::canBePlacedLike(char32_t character) const {
    switch(character) {
        case U'⿸': return placementFlags & 1;
        case U'⿹': return placementFlags & 2;
        case U'⿺': return placementFlags & 4;
        case U'⿴': return placementFlags & 8;
        case U'⿵': return placementFlags & 16;	
        case U'⿶': return placementFlags & 32;	
        case U'⿷': return placementFlags & 64;	
        default: return false;
    }
}

void Character::setPlacementFlag(char32_t character, bool value) {
    switch(character) {
        case U'⿸': util::setBit(&placementFlags, 0, value); return;
        case U'⿹': util::setBit(&placementFlags, 1, value); return;
        case U'⿺': util::setBit(&placementFlags, 2, value); return;
        case U'⿴': util::setBit(&placementFlags, 3, value); return;	
        case U'⿵': util::setBit(&placementFlags, 4, value); return;		
        case U'⿶': util::setBit(&placementFlags, 5, value); return;			
        case U'⿷': util::setBit(&placementFlags, 6, value); return;
        default: return;
    }
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

std::shared_ptr<Ingredient> Character::addLeft(std::shared_ptr<Character> character) {
    return std::make_shared<Recipe>(U'⿰', 
                                    std::vector<std::shared_ptr<Ingredient>>{
                                        std::dynamic_pointer_cast<Ingredient>(character), 
                                        std::dynamic_pointer_cast<Ingredient>(crafting::getCharacter(this->getCharacter()))});
}

std::shared_ptr<Ingredient> Character::addRight(std::shared_ptr<Character> character) {
    return std::make_shared<Recipe>(U'⿰', 
                                    std::vector<std::shared_ptr<Ingredient>>{
                                        std::dynamic_pointer_cast<Ingredient>(crafting::getCharacter(this->getCharacter())), 
                                        std::dynamic_pointer_cast<Ingredient>(character)});
}

std::shared_ptr<Ingredient> Character::addAbove(std::shared_ptr<Character> character) {
    return std::make_shared<Recipe>(U'⿱', 
                                    std::vector<std::shared_ptr<Ingredient>>{
                                        std::dynamic_pointer_cast<Ingredient>(character), 
                                        std::dynamic_pointer_cast<Ingredient>(crafting::getCharacter(this->getCharacter()))});
}

std::shared_ptr<Ingredient> Character::addBelow(std::shared_ptr<Character> character) {
    return std::make_shared<Recipe>(U'⿱', 
                                    std::vector<std::shared_ptr<Ingredient>>{
                                        std::dynamic_pointer_cast<Ingredient>(crafting::getCharacter(this->getCharacter())), 
                                        std::dynamic_pointer_cast<Ingredient>(character)});
}

void Character::addRecipe(std::u32string recipeString) {
    const char32_t* firstChar = recipeString.c_str();	
    recipes.emplace_back(Recipe(recipeString));
}

} // namespace crafting