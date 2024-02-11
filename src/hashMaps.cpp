#include "hashMaps.h"
#include "stringUtil.h"
#include <iostream>

namespace crafting {

    std::unordered_map<Recipe, std::shared_ptr<Character>> recipeMap;

    std::unordered_map<char32_t, std::shared_ptr<Character>> characterMap;

    bool registerRecipe(char32_t result, std::u32string recipeString) {
        if(recipeString.find(U"？") != std::u32string::npos || recipeString.find(U"{") != std::u32string::npos) {
            // std::cerr << "Recipe contains unknown character." << std::endl;
            return false;
        }
        if(recipeMap[recipeString]) {
            //std::cerr << "Recipe already registered." << std::endl;
            return false;
        }
        std::shared_ptr<Character> character = getCharacter(result);
        try {
            Recipe recipe(recipeString);
            recipeMap[recipe] = character;
            character->addRecipe(recipe);
            return true;
        }
        catch(std::runtime_error& e) {
            // pass
            throw std::runtime_error("Failed to register recipe: " + util::u32_to_u8(recipeString) + " for character: " + util::u32_to_u8(std::u32string(1, result)) + " with error: " + e.what());
            return false;
        }
    }

    std::shared_ptr<Character> getCharacter(char32_t character) {
        if(!characterMap[character]) {
            characterMap[character] = std::make_shared<Character>(character);
        }
        return characterMap[character];
    }

} // namespace crafting