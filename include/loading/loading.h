#ifndef LOADING_H
#define LOADING_H

#include <string>

namespace loading {

/**
 * @brief Loads the recipes from the all IDS files.
 * @throws std::runtime_error if the IDS file could not be opened or if the file is invalid.
*/
extern void loadRecipes();

/**
 * @brief Loads the recipes from a given IDS file.
 * @throws std::runtime_error if the IDS file could not be opened or if the file is invalid.
*/
extern void loadRecipes(std::string path);

/**
 * @brief Loads the meanings from the unihan readings file.
*/
extern void loadMeanings();

/**
 * @brief Loads hardcoded flags for some characters.
*/
extern void loadCharacterFlags();

/**
 * @brief Loads the FreeType library and fonts.
*/
extern void loadFreeType();

/**
 * @brief Loads all the data.
*/
extern void loadAll();

}


#endif // ifndef LOADING_H