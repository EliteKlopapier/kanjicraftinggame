#include "Bitmap.h"

namespace rendering {

GreyPixel GreyPixel::overlay(const GreyPixel& other) const {
    return GreyPixel(std::max(white, other.white));
}

GreyPixel GreyPixel::invert() const {
    return GreyPixel(uint8_t(255 - white));
}

Grey32Pixel::Grey32Pixel(const GreyPixel& grey) : white(grey.white) {}

Grey32Pixel Grey32Pixel::overlay(const Grey32Pixel& other) const {
    return Grey32Pixel(std::max(white, other.white));
}

Grey32Pixel Grey32Pixel::invert() const {
    return Grey32Pixel(0xFFFFFFFF - white);
}

RGB_Pixel::RGB_Pixel(const GreyPixel& grey)
    : red(grey.white)
    , green(grey.white)
    , blue(grey.white) {}

RGB_Pixel RGB_Pixel::overlay(const RGB_Pixel& other) const {
    return RGB_Pixel((red + other.red) / 2, 
                     (green + other.green) / 2, 
                     (blue + other.blue) / 2);
}

RGB_Pixel RGB_Pixel::invert() const {
    return RGB_Pixel(255 - red, 255 - green, 255 - blue);
}

RGBA_Pixel::RGBA_Pixel(const GreyPixel& grey)
    : red(255)
    , green(255)
    , blue(255)
    , alpha(grey.white) {}
RGBA_Pixel::RGBA_Pixel(const RGB_Pixel& rgb)
    : red(rgb.red)
    , green(rgb.green)
    , blue(rgb.blue)
    , alpha(255) {}

RGBA_Pixel RGBA_Pixel::overlay(const RGBA_Pixel& other) const {
    float alpha1 = alpha / 255.0f;
    float alpha2 = other.alpha / 255.0f;
    float alpha_out = alpha1 + alpha2 * (1 - alpha1);

    if (alpha_out == 0) {
        return RGBA_Pixel(0, 0, 0, 0);
    }

    uint8_t red_out = (red * alpha1 + other.red * alpha2 * (1 - alpha1)) / alpha_out;
    uint8_t green_out = (green * alpha1 + other.green * alpha2 * (1 - alpha1)) / alpha_out;
    uint8_t blue_out = (blue * alpha1 + other.blue * alpha2 * (1 - alpha1)) / alpha_out;
    uint8_t alpha_out_byte = alpha_out * 255;

    return RGBA_Pixel(red_out, green_out, blue_out, alpha_out_byte);
}

RGBA_Pixel RGBA_Pixel::invert() const {
    return RGBA_Pixel(255 - red, 255 - green, 255 - blue, alpha);
}

} // namespace rendering