#include "loading.h"
#include "freeTypeStuff.h"
#include "config.h"
#include <stdexcept>
#include <iostream>

namespace loading {

void loadFreeType() {
    FT_Error error = FT_Init_FreeType(&rendering::freeTypeLib);
    if(error) {
        throw std::runtime_error("Failed to initialize FreeType library");
    }
    error = FT_New_Face(rendering::freeTypeLib, "resources/fonts/HanaMinA.otf", 0, &rendering::hanaA);
    if(error) {
        throw std::runtime_error("Failed to load font HanaMinA");
    }
    error = FT_New_Face(rendering::freeTypeLib, "resources/fonts/HanaMinB.otf", 0, &rendering::hanaB);
    if(error) {
        throw std::runtime_error("Failed to load font HanaMinB");
    }
    error = FT_New_Face(rendering::freeTypeLib, "resources/fonts/HanaMinC.otf", 0, &rendering::hanaC);
    if(error) {
        throw std::runtime_error("Failed to load font HanaMinC");
    }
    // //error = FT_Set_Pixel_Sizes(rendering::hanaA, 600, 300);
    // error = FT_Set_Char_Size(rendering::hanaA, 0, 16 * 64, 300, 300);
    // if(error) {
    //     throw std::runtime_error("Failed to set character size for HanaMinA");
    // }
    // error = FT_Set_Char_Size(rendering::hanaB, 0, 16 * 64, 300, 300);
    // if(error) {
    //     throw std::runtime_error("Failed to set character size for HanaMinB");
    // }
    // error = FT_Set_Char_Size(rendering::hanaC, 0, 16 * 64, 300, 300);
    // if(error) {
    //     throw std::runtime_error("Failed to set character size for HanaMinC");
    // }

    #ifdef VERBOSE
    std::cout << "Successfully loaded FreeType and fonts with " 
        << (rendering::hanaA->num_glyphs + rendering::hanaB->num_glyphs + rendering::hanaC->num_glyphs) 
        << " glyphs." << std::endl;
    #endif
}

} // namespace loading