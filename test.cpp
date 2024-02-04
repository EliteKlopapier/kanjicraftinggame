#include <iostream>
#include "Character.h"
#include "StringUtil.h"

using namespace crafting;

int main() {
    Character c(U'木');
    c.addMeaning("tree");
    c.addMeaning("wood");
    Recipe r(U"⿻十𠆢");
    Recipe r2(U"⿻𠆢十");
    c.addRecipe(r);

    std::cout << "Recipes equal? " << (r == r2) << std::endl;

    std::cout << util::u32_to_u8(std::u32string(c.getRecipes()[0]));


    
    return 0;
}
