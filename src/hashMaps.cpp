#include "hashMaps.h"
#include "stringUtil.h"
#include "config.h"
#include <iostream>

namespace crafting {

    std::unordered_map<Recipe, std::shared_ptr<Character>> recipeMap;

    std::unordered_map<char32_t, std::shared_ptr<Character>> characterMap;

    bool registerRecipe(char32_t result, std::u32string recipeString) {
        if(recipeString.find(U"？") != std::u32string::npos || recipeString.find(U"{") != std::u32string::npos) {
            // std::cerr << "Recipe contains unknown character." << std::endl;
            return false;
        }
        if(recipeMap[recipeString]) {
            //std::cerr << "Recipe already registered." << std::endl;
            return false;
        }
        std::shared_ptr<Character> character = getCharacter(result);
        try {
            Recipe recipe(recipeString);
            recipeMap[recipe] = character;
            character->addRecipe(recipe);
            return true;
        }
        catch(std::runtime_error& e) {
            // pass
            throw std::runtime_error("Failed to register recipe: " + util::u32_to_u8(recipeString) + " for character: " + util::u32_to_u8(std::u32string(1, result)) + " with error: " + e.what());
            return false;
        }
    }

    bool registerMeanings(char32_t character, std::vector<std::string> meanings) {
        if(meanings.size() == 0) {
            return false;
        }
        std::shared_ptr<Character> c = getCharacter(character);
        int numAdded = 0;
        for(std::string& meaning : meanings) {
            // we don't want to add meanings that are not related to the character's meaning, like whether it's a radical or not
            if(meaning.find("radical") == std::string::npos) {
                auto infoAndMeaning = util::findEnclosedStrings<char>(meaning, '(', ')');
                std::string meaningToAdd = infoAndMeaning.second;
                bool containsJ = false;
                bool containsCant = false;
                for(auto& info : infoAndMeaning.first) {
                    if(info.find("J") != std::string::npos) {
                        containsJ = true;
                        //break;
                    }
                    else if(info.find("Cant.") != std::string::npos) {
                        containsCant = true;
                    }
                    else if(info.find("form") == std::string::npos && info.find("same as") == std::string::npos && info.find("variant") == std::string::npos && info.find("dialect") == std::string::npos && info.find("interchangeable") == std::string::npos && info.find("archaic") == std::string::npos && info.find("non-classical")  == std::string::npos && info.find("+") == std::string::npos) {
                        //std::cout << "Info at line " << lineNum << ": " << info << std::endl;
                        meaningToAdd += " (" + info + ")";
                    }
                }
                if((containsJ && ADDITIONAL_DEFINITIONS != 'J') || (containsCant && ADDITIONAL_DEFINITIONS != 'C')) {
                    continue;
                }
                c->addMeaning(meaningToAdd);
                numAdded++;
            }
            
        }
        return numAdded;
    }

    bool registerMeanings(char32_t character, std::string meanings) {
        std::vector<std::string> meaningVec = util::split<char>(meanings, ",;");
        return registerMeanings(character, meaningVec);
    }

    std::shared_ptr<Character> getCharacter(char32_t character) {
        if(!characterMap[character]) {
            characterMap[character] = std::make_shared<Character>(character);
        }
        return characterMap[character];
    }

} // namespace crafting