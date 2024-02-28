#ifndef LOADING_H
#define LOADING_H

namespace loading {

/**
 * @brief Loads the recipes from the IDS file.
*/
extern void loadRecipes();

/**
 * @brief Loads the meanings from the unihan readings file.
*/
extern void loadMeanings();

/**
 * @brief Loads the FreeType library and fonts.
*/
extern void loadFreeType();

}


#endif // ifndef LOADING_H