#ifndef PIXELS_H
#define PIXELS_H

#include <cstdint>

namespace rendering {

/**
 * A greyscale pixel represented by 8 bits.
*/
struct GreyPixel {
    uint8_t white;
    static constexpr int NUM_CHANNELS = 1;
    constexpr GreyPixel() : white(0) {}
    constexpr GreyPixel(uint8_t white) : white(white) {}
    constexpr GreyPixel(float brightness) : white(brightness * 255) {}
    GreyPixel overlay(const GreyPixel& other) const;
    GreyPixel invert() const;
};

/**
 * A greyscale pixel represented by 32 bits.
*/
struct Grey32Pixel {
    uint32_t white;
    static constexpr int NUM_CHANNELS = 1;
    constexpr Grey32Pixel() : white(0) {}
    constexpr Grey32Pixel(uint8_t white) : white(white) {}
    constexpr Grey32Pixel(float brightness) : white(brightness * 0xFFFFFFFF) {}
    constexpr Grey32Pixel(uint32_t white) : white(white) {}
    Grey32Pixel(const GreyPixel& grey);
    Grey32Pixel overlay(const Grey32Pixel& other) const;
    Grey32Pixel invert() const;
};

/**
 * An RGB pixel with one byte per channel.
*/
struct RGB_Pixel {
    uint8_t red, green, blue;
    static constexpr int NUM_CHANNELS = 3;
    constexpr RGB_Pixel()
        : red(0)
        , green(0)
        , blue(0) {}
    constexpr RGB_Pixel(uint8_t white) 
        : red(white)
        , green(white)
        , blue(white) {}
    constexpr RGB_Pixel(float brightness)
        : red(brightness * 255)
        , green(brightness * 255)
        , blue(brightness * 255) {}
    constexpr RGB_Pixel(uint8_t red, uint8_t green, uint8_t blue)
        : red(red)
        , green(green)
        , blue(blue) {}
    RGB_Pixel(const GreyPixel& grey);
    RGB_Pixel overlay(const RGB_Pixel& other) const;
    RGB_Pixel invert() const;
};

/**
 * An RGBA pixel with one byte per channel.
 * @note Constructing an RGBA pixel from a uint8_t value or a greyscale pixel will interpret that (greyscale) value as the alpha value.
*/
struct RGBA_Pixel {
    uint8_t red, green, blue, alpha;
    static constexpr int NUM_CHANNELS = 4;
    constexpr RGBA_Pixel()
        : red(0)
        , green(0)
        , blue(0)
        , alpha(0) {}
    constexpr RGBA_Pixel(uint8_t white)
        : red(255)
        , green(255)
        , blue(255)
        , alpha(white) {}
    constexpr RGBA_Pixel(float brightness)
        : red(brightness * 255)
        , green(brightness * 255)
        , blue(brightness * 255)
        , alpha(255) {}
    constexpr RGBA_Pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
        : red(red)
        , green(green)
        , blue(blue)
        , alpha(alpha) {}
    RGBA_Pixel(const GreyPixel& grey);
    RGBA_Pixel(const RGB_Pixel& rgb);
    RGBA_Pixel overlay(const RGBA_Pixel& other) const;
    RGBA_Pixel invert() const;
};

} // namespace rendering

#endif // ifndef PIXELS_H