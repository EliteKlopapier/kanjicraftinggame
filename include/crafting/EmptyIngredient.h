
#ifndef EMPTY_INGREDIENT_H
#define EMPTY_INGREDIENT_H

#include "Ingredient.h"
#include "Character.h"
#include <memory>

namespace crafting {

class EmptyIngredient : public Ingredient {
public:
    bool operator==(const Ingredient& other) const override;
    operator std::u32string() const override;
    rendering::Bitmap render(int width, int height) const override;
    std::shared_ptr<Ingredient> addLeft(std::shared_ptr<Character> character) const override;
    std::shared_ptr<Ingredient> addRight(std::shared_ptr<Character> character) const override;	
    std::shared_ptr<Ingredient> addAbove(std::shared_ptr<Character> character) const override;		
    std::shared_ptr<Ingredient> addBelow(std::shared_ptr<Character> character) const override;	
};

} // namespace crafting

#endif // EMPTY_INGREDIENT_H
