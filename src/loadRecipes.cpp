#include "loadRecipes.h"
#include "config.h"
#include "stringUtil.h"
#include "hashMaps.h"
#include <fstream>
#include <string>
#include <vector>
#include <string>
#ifdef VERBOSE 
    #include <iostream>
#endif

namespace loading {

/**
 * @brief Loads the recipes from the IDS file.
 * @throws std::runtime_error if the IDS file could not be opened or if the file is invalid.
*/
void loadRecipes() {
    std::ifstream idsFile;
    idsFile.open(IDS_PATH);
    std::string line;
    if(!idsFile) {
        idsFile.open(std::string("../") + IDS_PATH); // if executable is in build directory
    }
    if(idsFile) {
        #ifdef VERBOSE
            std::cout << "Loading recipes from " << IDS_PATH << std::endl;
            int numSuccess = 0;
        #endif
        int lineNum = 0;
        while(std::getline(idsFile, line)) {
            lineNum++;
            if(line[0] == '#') {
                continue;
            }
            std::vector<std::string> columns = util::split<char>(line, '\t');
            std::string character = columns[1];
            std::vector<std::pair<std::string, std::string>> recipes;
            std::vector<std::string> alternateRecipes;
            for(int i = 2; i < columns.size(); i++) {
                std::string recipe = columns[i];
                if(recipe[0] == '^') {
                    int dollarPos = recipe.find('$');
                    if(dollarPos == std::string::npos) {
                        throw std::runtime_error("Invalid recipe format at line " + std::to_string(lineNum) + " in IDS file. Missing dollar sign.");
                    }
                    std::string flags = recipe.substr(dollarPos + 1);
                    recipe = recipe.substr(1, dollarPos - 1);
                    std::u32string u32recipe = util::u8_to_u32(recipe);
                    if(flags == "(UCS2003)" || flags == "(Z)" || u32recipe.size() <= 1 || (u32recipe[0] == U'〾' && u32recipe.size() <= 2)) {
                        continue;
                    }
                    else if(flags == "(X)") {
                        alternateRecipes.push_back(recipe);                    
                    }
                    else {
                        recipes.push_back({recipe, flags});
                    }
                }
            }
            if(recipes.size() > 0) {
                std::string recipeString;
                int max = 0;
                int maxIndex = 0;
                bool inserted = false;
                // Besides the alternate recipes, marked with X, from the other recipes we select the one for the preferred variant if it exists,
                // otherwise we select the one used in most countries
                for(int i = 0; i < recipes.size(); i++) {
                    std::string r = recipes[i].first;
                    std::string flags = recipes[i].second;
                    if(flags.find(PREFERRED_VARIANT) != std::string::npos) {
                        recipeString = r;
                        inserted = true;
                        break;
                    }
                    else {
                        if(flags.size() > max) {
                            max = flags.size();
                            maxIndex = i;
                        }
                    }
                }
                if(!inserted) {
                    recipeString = recipes[maxIndex].first;
                }
                std::u32string u32char = util::u8_to_u32(character);
                if(u32char.size() > 1) {
                    throw std::runtime_error("Invalid character at line " + std::to_string(lineNum) + ". Length > 1.");
                }
                #ifdef VERBOSE
                    numSuccess +=
                #endif
                crafting::registerRecipe(u32char[0], util::u8_to_u32(recipeString));
                
            }
            for(std::string& alt : alternateRecipes) {
                std::u32string u32char = util::u8_to_u32(character);
                if(u32char.size() > 1) {
                    throw std::runtime_error("Invalid character at line " + std::to_string(lineNum) + ". Length > 1.");
                }
                #ifdef VERBOSE
                    numSuccess +=
                #endif
                crafting::registerRecipe(u32char[0], util::u8_to_u32(alt));
            }
        }
        idsFile.close();
        #ifdef VERBOSE
            std::cout << "Successfully loaded " << numSuccess << " recipes." << std::endl;
        #endif
    }
    else {
        throw std::runtime_error("Could not open IDS file.");
    }
}

}