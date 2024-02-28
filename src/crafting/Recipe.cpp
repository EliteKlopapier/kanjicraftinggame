#include "Recipe.h"
#include "Character.h"
#include "stringUtil.h"
#include "hashMaps.h"
#include <iostream>

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

static int findRecipeSubstrLength(const std::u32string& recipeString, int startPos) {
    //std::cout << "Finding recipe substr length for " << util::u32_to_u8(recipeString) << " at " << startPos << std::endl;
    Operator& op = operators[recipeString[startPos]];
    //std::cout << "Found operator " << op.operator_c << " with " << op.num_ingredients << " ingredients" << std::endl;
    int pos = startPos + 1;
    for(int i = 0; i < op.num_ingredients; i++) {
        if(operators[recipeString[pos]]) {
            pos += findRecipeSubstrLength(recipeString, pos);
        }
        else {
            pos++;
        }
    }
    //std::cout << "Found recipe substr length for " << util::u32_to_u8(recipeString) << " at " << startPos << " to be " << pos - startPos << std::endl;
    return pos - startPos;
}

Recipe::Recipe(std::u32string recipeString) 
    : mIngredients()
    , mOperator(recipeString[0] == U'〾' ? operators[recipeString[1]] : operators[recipeString[0]])
    , approx(recipeString[0] == U'〾')
{
    if(approx) {
        recipeString = recipeString.substr(1);
    }
    const char32_t* charPtr = recipeString.data();
    if (!operators[*charPtr]) {
        throw std::runtime_error("First character of recipe string must be an operator, but instead is " + util::u32_to_u8(std::u32string(1, *charPtr)));
    }
    charPtr++;
    int pos = 1;
    for(int i = 0; i < mOperator.num_ingredients; i++) {
        if(pos >= recipeString.size()) {
            throw std::runtime_error("Not enough ingredients in recipe string.");// Debug info: currently constructung " + util::u32_to_u8(recipeString) + ". Pos is at " + std::to_string(pos) + " and recipeString.size() is " + std::to_string(recipeString.size()) + ". i is at " + std::to_string(i) + ".");
        }
        else if(operators[*charPtr]) {
            int len = findRecipeSubstrLength(recipeString, pos);
            if(pos + len > recipeString.size()) {
                throw std::runtime_error("Not enough ingredients in recipe string. Pos is at " + std::to_string(pos) + " and recipeString.size() is " + std::to_string(recipeString.size()) + ". i is at " + std::to_string(i) + ". len is at " + std::to_string(len) + ". While constructing " + util::u32_to_u8(recipeString) + ".");
            }
            mIngredients.emplace_back(new Recipe(recipeString.substr(pos, len)));
            pos += len;
            charPtr += len;
        }
        else {
            mIngredients.emplace_back(crafting::getCharacter(*charPtr));
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
    if(mOperator.operator_c != other.getOperator().operator_c
            || approx != other.getApprox()) {
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

rendering::Bitmap Recipe::render(int width, int height) const {
    switch(mOperator.operator_c) {
        case U'↔': return mIngredients[0]->render(width, height).mirror();
        case U'↷': return mIngredients[0]->render(width, height).rotate180();
        case U'⊖': return rendering::Bitmap(width, height); // not intended to be rendered
		case U'⿰': return mIngredients[0]->render(width/2 + ((width%2) ? 1 : 0), height).joinHorizontally(mIngredients[1]->render(width/2, height));
		case U'⿱': return mIngredients[0]->render(width, height/2 + ((height%2) ? 1 : 0)).joinVertically(mIngredients[1]->render(width, height/2));
		case U'⿲': {
			int rest = width % 3;
			return mIngredients[0]->render(width/3 + (rest ? 1 : 0), height).joinHorizontally(
				   mIngredients[1]->render(width/3 + (rest==2) ? 1 : 0, height).joinHorizontally(
				   mIngredients[2]->render(width/3, height)));
		}
        case U'⿳': {
            int rest = height % 3;
			return mIngredients[0]->render(width, height/3 + (rest ? 1 : 0)).joinVertically(
				   mIngredients[1]->render(width, height/3 + (rest==2) ? 1 : 0).joinVertically(
				   mIngredients[2]->render(width, height/3)));
        }
        case U'⿴': return mIngredients[0]->render(width, height).overlay(mIngredients[1]->render(width/2, height/2).placeOnCanvas(width, height));
        case U'⿵': return mIngredients[0]->render(width, height).overlay(mIngredients[1]->render(width/3, height*2/3).placeOnCanvas(width, height, width/3, height/3));
        case U'⿶': return mIngredients[0]->render(width, height).overlay(mIngredients[1]->render(width/3, height*2/3).placeOnCanvas(width, height, width/3, 0));
        case U'⿷': return mIngredients[0]->render(width, height).overlay(mIngredients[1]->render(width*2/3, height/3).placeOnCanvas(width, height, width/3, height/3)); 
        case U'⿸': return mIngredients[0]->render(width, height).overlay(mIngredients[1]->render(width*2/3, height*2/3).placeOnCanvas(width, height, width/3, height/3));
        case U'⿹': return mIngredients[0]->render(width, height).overlay(mIngredients[1]->render(width*2/3, height*2/3).placeOnCanvas(width, height, 0, height/3));
        case U'⿺': return mIngredients[0]->render(width, height).overlay(mIngredients[1]->render(width*2/3, height*2/3).placeOnCanvas(width, height, width/3, 0));
        case U'⿻': return mIngredients[0]->render(width, height).overlay(mIngredients[1]->render(width, height));
        default: return rendering::Bitmap(width, height);
    }
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