#include <iostream>
#include "Character.h"
#include "stringUtil.h"
#include "hashMaps.h"
#include "loading.h"
#include "Consumable.h"

using namespace crafting;

int main() {

    //registerRecipe(U'木', U"⿻十𠆢");

    loading::loadRecipes();
    loading::loadMeanings();

    getCharacter(U'木')->addFunctionality(std::make_unique<items::HealthConsumable>(10));
    std::cout << "Functionality of 木: " << getCharacter(U'木')->getFunctionalities()[0]->getDescription() << std::endl;

    std::cout << "Recipe for 木: " << util::u32_to_u8(getCharacter(U'木')->getRecipes()[0]) << std::endl;
    std::cout << "Result of ⿻𠆢十: " << util::u32_to_u8(*recipeMap[Recipe(U"⿻十𠆢")][0]) << std:: endl;
    std::cout << "Meanings of 木: ";
    for(auto& meaning : getCharacter(U'木')->getMeanings()) {
        std::cout << meaning << ", ";
    }
    std::cout << std::endl;

    std::cout << util::u32_to_u8(std::u32string(1, util::unicodeToChar("U+4E1A"))) << std::endl;

    
    return 0;
}
