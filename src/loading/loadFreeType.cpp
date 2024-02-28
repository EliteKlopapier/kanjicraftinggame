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
    error = FT_New_Face(rendering::freeTypeLib, (std::string("resources/fonts/NotoSerif") + FONT + "-Regular.otf").c_str(), 0, &rendering::fontFace);
    if(error) {
        throw std::runtime_error("Failed to load font.");
    }

    #ifdef VERBOSE
    std::cout << "Successfully loaded FreeType and fonts with " 
        << (rendering::fontFace->num_glyphs + rendering::fontFace->num_glyphs + rendering::fontFace->num_glyphs) 
        << " glyphs." << std::endl;
    #endif
}

} // namespace loading