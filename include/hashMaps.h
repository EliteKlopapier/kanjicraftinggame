#ifndef HASH_MAPS_H
#define HASH_MAPS_H

#include "Recipe.h"
#include "Character.h"

namespace crafting {
    // A map to look up the result of a recipe.
    extern std::unordered_map<Recipe, std::shared_ptr<Character>> recipeMap;
    // A map to look up the data related to a UTF-32 character.
    extern std::unordered_map<char32_t, std::shared_ptr<Character>> characterMap;

    /**
     * @brief Registers a recipe with the given result and recipe string.
     * @return True if the recipe was successfully registered, false otherwise.
    */
    bool registerRecipe(char32_t result, std::u32string recipeString);
}

#endif // ifndef HASH_MAPS_H