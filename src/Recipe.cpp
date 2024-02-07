#include "Recipe.h"
#include "Character.h"

namespace crafting {

std::unordered_map<char32_t, Operator> operators{
    {U'↔', {U'↔', 1, true}},
    {U'↷', {U'↷', 1, true}},
    {U'⊖', {U'⊖', 2, true}},
    {U'⿰', {U'⿰', 2, true}},
    {U'⿱', {U'⿱', 2, true}},
    {U'⿲', {U'⿲', 3, true}},
    {U'⿳', {U'⿳', 3, true}},
    {U'⿴', {U'⿴', 2, true}},
    {U'⿵', {U'⿵', 2, true}},
    {U'⿶', {U'⿶', 2, true}},
    {U'⿷', {U'⿷', 2, true}},
    {U'⿸', {U'⿸', 2, true}},
    {U'⿹', {U'⿹', 2, true}},
    {U'⿺', {U'⿺', 2, true}},
    {U'⿻', {U'⿻', 2, false}}
};

Recipe::Recipe(Operator& op, std::initializer_list<std::shared_ptr<Ingredient>> ingredients) 
    : mIngredients(ingredients) 
    , mOperator(op)
{
    if(mIngredients.size() != mOperator.num_ingredients) {
        throw std::runtime_error("Number of ingredients does not match operator");
    }
}

Recipe::Recipe(std::u32string recipeString) 
    : mIngredients()
    , mOperator(operators[recipeString[0]])
    , approx(recipeString[0] == U'〾')
{
    if(approx) {
        recipeString = recipeString.substr(1);
    }
    const char32_t* charPtr = recipeString.data();
    if (!operators[*charPtr]) {
        throw std::runtime_error("First character of recipe string must be an operator");
    }
    charPtr++;
    int pos = 1;
    for(int i = 0; i < mOperator.num_ingredients; i++) {
        if(pos >= recipeString.size()) {
            throw std::runtime_error("Not enough ingredients in recipe string");
        }
        else if(operators[*charPtr]) {
            if(pos + operators[*charPtr].num_ingredients > recipeString.size()) {
                throw std::runtime_error("Not enough ingredients in recipe string");
            }
            mIngredients.emplace_back(new Recipe(recipeString.substr(pos, operators[*charPtr].num_ingredients + 1)));
            charPtr += operators[*charPtr].num_ingredients + 1;
            pos += operators[*charPtr].num_ingredients + 1;
        }
        else {
            mIngredients.emplace_back(new Character(*charPtr));
            charPtr++;
            pos++;
        }
    }
    if(pos < recipeString.size()) {
        throw std::runtime_error("Too many ingredients in recipe string. Pos is at " + std::to_string(pos) + " and recipeString.size() is " + std::to_string(recipeString.size()));
    }
}

bool Recipe::operator==(const Ingredient& other) const {
    const Recipe* otherRecipe = dynamic_cast<const Recipe*>(&other);
    if(otherRecipe == nullptr) {
        return false;
    }
    else {
        return *this == *otherRecipe;
    }
}

bool Recipe::operator==(const Recipe& other) const {
    if(mOperator.operator_c != other.getOperator().operator_c) {
        return false;
    }
    else {
        if(mIngredients.size() != other.getIngredients().size()) {
            return false;
        }
        else if(mOperator.ordered) {
            for(int i = 0; i < mIngredients.size(); i++) {
                if(!(*mIngredients[i] == *other.getIngredients()[i])) {
                    return false;
                }
            }
            return true;
        }
        else {
            for(int i = 0; i < mIngredients.size(); i++) {
                bool found = false;
                for(int j = 0; j < other.getIngredients().size(); j++) {
                    if(*mIngredients[i] == *other.getIngredients()[j]) {
                        found = true;
                        break;
                    }
                }
                if(!found) {
                    return false;
                }
            }
            return true;
        }
    }
}

Recipe::operator std::u32string() const {
    std::u32string recipeString;
    if(approx) {
        recipeString += U'〾';
    }
    recipeString += mOperator.operator_c;
    for(int i = 0; i < mIngredients.size(); i++) {
        recipeString += std::u32string(*mIngredients[i]);
    }
    return recipeString;
}

} // namespace crafting

namespace std {
    size_t hash<crafting::Recipe>::operator()(const crafting::Recipe& recipe) const {
        u32string recipeString(recipe);
        size_t hash = 0;
        for(char32_t c : recipeString) {
            hash ^= c;
        }
        return hash;
    }
}