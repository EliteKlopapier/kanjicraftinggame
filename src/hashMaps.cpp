#include "hashMaps.h"
#include <iostream>

namespace crafting {

    std::unordered_map<Recipe, std::shared_ptr<Character>> recipeMap;

    std::unordered_map<char32_t, std::shared_ptr<Character>> characterMap;

    bool registerRecipe(char32_t result, std::u32string recipeString) {
        std::shared_ptr<Character> character;
        if(characterMap[result]) {
            character = characterMap[result];
        }
        else {
            character = std::make_shared<Character>(result);
            characterMap[result] = character;
        }
        try {
            Recipe recipe(recipeString);
            recipeMap[recipe] = character;
            character->addRecipe(recipe);
            return true;
        }
        catch(std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
            return false;
        }
    }

} // namespace crafting