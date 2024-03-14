#ifndef INGREDIENT_H
#define INGREDIENT_H

#include "Bitmap.h"
#include <string>
#include <memory>

namespace crafting {

class Character;

/**
 * @brief An interface for components of a recipe.
*/
class Ingredient {
public:
    virtual bool operator==(const Ingredient& other) const = 0;
    virtual operator std::u32string() const = 0;
    /**
     * @brief Render the ingredient as a bitmap with the given dimensions.
    */
    virtual rendering::Bitmap render(int width, int height) const = 0;
    /**
     * @brief Add a character to the left of the ingredient.
    */
    virtual std::shared_ptr<Ingredient> addLeft(std::shared_ptr<Character> character) = 0;
    /**
     * @brief Add a character to the right of the ingredient.
    */	
    virtual std::shared_ptr<Ingredient> addRight(std::shared_ptr<Character> character) = 0;	
    /**
     * @brief Add a character above the ingredient.
    */	
    virtual std::shared_ptr<Ingredient> addAbove(std::shared_ptr<Character> character) = 0;
    /**
     * @brief Add a character below the ingredient.
    */		
    virtual std::shared_ptr<Ingredient> addBelow(std::shared_ptr<Character> character) = 0;	
};

} // namespace crafting

#endif // ifndef INGREDIENT_H