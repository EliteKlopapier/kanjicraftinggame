#ifndef RECIPE_H
#define RECIPE_H

#include "Ingredient.h"
#include <initializer_list>
#include <vector>
#include <unordered_map>
#include <memory>

namespace crafting {

/**
 * @brief An operator that defines how to combine ingredients in a recipe.
*/
struct {
    // The character that represents the operator.
    char32_t operator_c;
    // The number of ingredients that the operator takes.
    int num_ingredients;
    // Whether the ingredients must be in a specific order.
    bool ordered;
    // Whether the operator has been initialized.
    operator bool() { return operator_c; }
} typedef Operator;

// A hash map used to obtain an operator from its character representation.
extern std::unordered_map<char32_t, Operator> operators;

/**
 * @brief Ingredients put together with an operator to form a recipe.
*/
class Recipe : public Ingredient {
private:
    std::vector<std::shared_ptr<Ingredient>> mIngredients;
    Operator& mOperator;
public:
    /**
     * @brief Constructs a new Recipe object.
     * @param op The operator to use in the recipe.
     * @param ingredients The ingredients to use in the recipe.
     * @throws std::runtime_error If the number of ingredients does not match the operator.
    */
    Recipe(Operator& op, std::initializer_list<std::shared_ptr<Ingredient>> ingredients);
    /**
     * @brief Constructs a new Recipe object.
     * @param recipeString The string representation of the recipe.
     * @throws std::runtime_error If the first character of the recipe string or of substrings representing recipes are not operators.
     * @throws std::runtime_error If the number of ingredients does not match the operator.
    */
    Recipe(std::u32string recipeString);
    /**
     * @brief Gets the vector of pointers to ingredients used in the recipe.
    */
    std::vector<std::shared_ptr<Ingredient>>& getIngredients() { return mIngredients; }
    /**
     * @brief Gets the operator used in the recipe.
    */
    Operator& getOperator() { return mOperator; }
    bool operator==(Ingredient& other) override;
    bool operator==(Recipe& other);
    operator std::u32string() override;
};

} // namespace crafting

#endif // ifndef RECIPE_H