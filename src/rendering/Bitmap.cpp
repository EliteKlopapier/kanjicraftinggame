#include "Bitmap.h"
#include <stdexcept>
#include <math.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

namespace rendering {

Bitmap::Bitmap(FT_Bitmap& bitmap) 
    : width(bitmap.width)
    , height(bitmap.rows)
{
    switch(bitmap.pixel_mode) {
        case FT_PIXEL_MODE_MONO:
            throw std::invalid_argument("Unsupported pixel mode: FT_PIXEL_MODE_MONO");
        case FT_PIXEL_MODE_GRAY: {
            if(bitmap.num_grays != 256) {
                throw std::invalid_argument("Unsupported number of grays: " + std::to_string(bitmap.num_grays));
            }
            pixels = new uint8_t[width * height];
            uint8_t* buffer = bitmap.buffer;
            if(bitmap.pitch < 0) {
                buffer += bitmap.pitch * (height - 1);
            }
            memcpy(pixels, buffer, abs(bitmap.pitch) * height);
            break;
        }
        case FT_PIXEL_MODE_GRAY2:
            throw std::invalid_argument("Unsupported pixel mode: FT_PIXEL_MODE_GRAY2");
        case FT_PIXEL_MODE_GRAY4:
            throw std::invalid_argument("Unsupported pixel mode: FT_PIXEL_MODE_GRAY4");
        case FT_PIXEL_MODE_LCD:
            throw std::invalid_argument("Unsupported pixel mode: FT_PIXEL_MODE_LCD");
        case FT_PIXEL_MODE_LCD_V:
            throw std::invalid_argument("Unsupported pixel mode: FT_PIXEL_MODE_LCD_V");
        default:
            throw std::invalid_argument("Unsupported pixel mode: " + std::to_string(bitmap.pixel_mode));
    }
}

Bitmap::Bitmap(int width, int height) : width(width), height(height) {
    pixels = new uint8_t[width * height];
    memset(pixels, 0, width * height);
}

Bitmap Bitmap::overlay(const Bitmap& other) const {
    if(width != other.width || height != other.height) {
        throw std::invalid_argument("Bitmaps must have the same dimensions to overlay");
    }
    Bitmap result(width, height);
    for(int i = 0; i < width * height; i++) {
        result.pixels[i] = std::max(pixels[i], other.pixels[i]);
    }
    return result;
}

Bitmap Bitmap::joinVertically(const Bitmap& other) const {
    if(width != other.width) {
        throw std::invalid_argument("Bitmaps must have the same width to join");
    }
    Bitmap result(width, height + other.height);
    memcpy(result.pixels, pixels, width * height);
    memcpy(result.pixels + width * height, other.pixels, width * other.height);
    return result;
}

Bitmap Bitmap::joinHorizontally(const Bitmap& other) const {
    if(height != other.height) {
        throw std::invalid_argument("Bitmaps must have the same height to join");
    }
    Bitmap result(width + other.width, height);
    for(int i = 0; i < height; i++) {
        memcpy(result.pixels + (width + other.width) * i, pixels + width * i, width);
        memcpy(result.pixels + (width + other.width) * i + width, other.pixels + other.width * i, other.width);
    }
    return result;
}

Bitmap Bitmap::placeOnCanvas(int canvasWidth, int canvasHeight, int x, int y) const {
    Bitmap result(canvasWidth, canvasHeight);
    if(x < 0 || y < 0 || x + width > canvasWidth || y + height > canvasHeight) {
        throw std::invalid_argument("Bitmap does not fit on canvas: placing bitmap with dimensions " + std::to_string(width) + "x" + std::to_string(height) + " at (" + std::to_string(x) + ", " + std::to_string(y) + ") on canvas with dimensions " + std::to_string(canvasWidth) + "x" + std::to_string(canvasHeight) + " is out of bounds.");
    }
    for(int i = 0; i < height; i++) {
        memcpy(result.pixels + (canvasWidth * (y + i) + x), pixels + width * i, width);
    }
    return result;
}

Bitmap Bitmap::placeOnCanvas(int canvasWidth, int canvasHeight) const {
    return placeOnCanvas(canvasWidth, canvasHeight, (canvasWidth - width) / 2, (canvasHeight - height) / 2);
}

Bitmap Bitmap::mirror() const {
    Bitmap result(width, height);
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            result.pixels[y * width + x] = pixels[y * width + width-1-x];
        }
    }
    return result;
}

Bitmap Bitmap::rotate180() const {
    Bitmap result(width, height);
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            result.pixels[(height-1-y) * width + x] = pixels[y * width + width-1-x];
        }
    }
    return result;
}

bool Bitmap::printToFile(const char* filename) const {
    int result = stbi_write_png(filename, width, height, 1, pixels, width);
    return result != 0;
}

} // namespace rendering