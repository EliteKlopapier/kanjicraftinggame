#include <iostream>
#include "Character.h"
#include "StringUtil.h"
#include "hashMaps.h"
#include "loadRecipes.h"

using namespace crafting;

int main() {

    //registerRecipe(U'木', U"⿻十𠆢");

    loading::loadRecipes();

    std::cout << "Recipe for 木: " << util::u32_to_u8(characterMap[U'木']->getRecipes()[0]) << std::endl;
    std::cout << "Result of ⿻𠆢十: " << util::u32_to_u8(*recipeMap[Recipe(U"⿻十𠆢")]) << std:: endl;
    
    return 0;
}
