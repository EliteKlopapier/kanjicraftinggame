#ifndef CHARACTER_H
#define CHARACTER_H

#include "Ingredient.h"
#include "Recipe.h"
#include <vector>

namespace crafting {

/**
 * @brief A Chinese character that can be obtained as an item by the player or referenced in a recipe.
*/
class Character : public Ingredient {
private:
    char32_t mCharacter;
    std::vector<std::string> meanings;
    std::vector<Recipe> recipes;
    std::vector<char32_t> alternatives;
public:
    /**
     * @brief Constructs an empty Character object.
    */
    Character() : mCharacter(0) {}
    /**
     * @brief Constructs a new Character object.
     * @param character The character to represent.
    */
    Character(char32_t character);
    bool operator==(const Ingredient& other) const;
    bool operator==(const Character& other) const;
    operator std::u32string() const;
    operator char32_t() const { return mCharacter; }
    /**
     * @brief Gets the character represented by this object.
    */
    char32_t getCharacter() const { return mCharacter; }
    /**
     * @brief Gets a vector of the meanings of the character represented by this object.
    */
    const std::vector<std::string>& getMeanings() const { return meanings; }
    /**
     * @brief Gets a vector of the recipes that can be used to obtain the character represented by this object.
    */
    const std::vector<Recipe>& getRecipes() const { return recipes; }
    /**
     * @brief Gets a vector of characters that are considered equivalent to the character represented by this object.
    */
    const std::vector<char32_t>& getAlternatives() const { return alternatives; }
    /**
     * @brief Adds a meaning to the character represented by this object.
    */
    void addMeaning(std::string meaning) { meanings.push_back(meaning); }
    /**
     * @brief Adds a recipe to the character represented by this object.
     * @param recipe The recipe to add.
    */
    void addRecipe(Recipe& recipe) { recipes.push_back(recipe); }
    /**
     * @brief Adds a recipe to the character represented by this object.
     * @param recipeString The string representation of the recipe to add.
    */
    void addRecipe(std::u32string recipeString);
};

} // namespace crafting

#endif // ifndef CHARACTER_H