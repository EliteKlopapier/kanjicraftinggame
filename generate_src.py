import json5 as json

config = json.load(open('config.json5'))

with open(config['idsFile'], 'r', encoding='utf-8') as ids, open('src/generated/loadRecipes.cpp', 'w', encoding='utf-8') as srcOut:
    srcOut.write("""
#include "hashMaps.h"
#include "loadRecipes.h"
#include <utility>

namespace loading {

std::pair<char32_t, std::u32string> rawRecpieData[] = {

""") 
    for line in ids:
        if line.startswith('#'):
            continue
        line = line.strip()
        columns = line.split('\t')
        char = columns[1]
        recipes = []
        alternateRecipes = []
        for i in range(2, len(columns)):
            recipe = columns[i]
            if recipe.startswith('^'):
                recipe = recipe[1:]
                recipe = recipe.split("$")
                if recipe[1] == '(UCS2003)' or recipe[1] == '(Z)' or len(recipe[0]) == 1:
                    continue
                elif recipe[1] == '(X)':
                    alternateRecipes.append(recipe[0])
                else: 
                    recipes.append(recipe)
        if len(recipes) > 0:
            recipe
            max = 0
            maxIndex = -1
            inserted = False
            # Besides the alternate recipes, marked with X, from the other recipes we select the one for the preferred variant if it exists,
            # otherwise we select the one used in most countries
            for i in range(len(recipes)):
                r = recipes[i]
                if(r[1].find(config['preferredVariant']) != -1):
                    recipe = r[0]
                    inserted = True
                    break
                else:
                    if len(r[1]) > max:
                        max = len(r[1])
                        maxIndex = i
            if not inserted:
                recipe = recipes[maxIndex][0]
            srcOut.write(f"\tstd::make_pair(U'{char}', U\"{recipe}\"),\n")
            for r in alternateRecipes:
                srcOut.write(f"\tstd::make_pair(U'{char}', U\"{r}\"),\n")
    # remove the last comma
    srcOut.seek(srcOut.tell() - 3)
    srcOut.write("\n};\n")
    srcOut.write("""
void loadRecipes() {
    for(auto& r : rawRecpieData) {
        crafting::registerRecipe(r.first, r.second);
    }
}
} // namespace loading
""")
    srcOut.close()
    ids.close()
