#include "loading.h"
#include "freeTypeStuff.h"
#include "config.h"
#include <stdexcept>
#include <iostream>
#include <string>

namespace loading {

void loadFreeType() {
    FT_Error error = FT_Init_FreeType(&rendering::freeTypeLib);
    if(error) {
        throw std::runtime_error("Failed to initialize FreeType library");
    }
    error = FT_New_Face(rendering::freeTypeLib, (std::string("resources/fonts/NotoSerif") + FONT + "-Regular.otf").c_str(), 0, &rendering::fontFaceMain);
    if(error) {
        throw std::runtime_error("Failed to load main font.");
    }
    error = FT_New_Face(rendering::freeTypeLib, "resources/fonts/BabelStoneHan.ttf", 0, &rendering::fontFaceBackUp1);
    if(error) {
        throw std::runtime_error("Failed to load backup font 1.");
    }
    error = FT_New_Face(rendering::freeTypeLib, "resources/fonts/BabelStoneHanPUA.ttf", 0, &rendering::fontFaceBackUp2);
    if(error) {
        throw std::runtime_error("Failed to load backup font 2.");
    }

    #ifdef VERBOSE
    std::cout << "Successfully loaded FreeType with " 
        << rendering::fontFaceMain->num_glyphs 
        << " glyphs in main font, "
        << rendering::fontFaceBackUp1->num_glyphs
        << " glyphs in backup font 1, and "
        << rendering::fontFaceBackUp2->num_glyphs
        << " glyphs in backup font 2." << std::endl;
    #endif
}

} // namespace loading