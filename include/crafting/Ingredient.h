#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>

namespace crafting {

/**
 * @brief An interface for components of a recipe.
*/
class Ingredient {
public:
    virtual bool operator==(const Ingredient& other) const = 0;
    virtual operator std::u32string() const = 0;
};

} // namespace crafting

#endif // ifndef INGREDIENT_H