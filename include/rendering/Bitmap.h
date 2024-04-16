#ifndef BITMAP_H
#define BITMAP_H

#include "Pixels.h"
#include "freeTypeStuff.h"
#include FT_BITMAP_H
#include <cstdint>
#include <stdexcept>
#include <math.h>
// #define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

namespace rendering {

/**
 * @brief A bitmap with a few utility functions.
 * @param Pixel A structure that represents a single pixel. Needs to fulfill the following requirements:
 * - implements a function `Pixel overlay(const Pixel&)` 
 * - implements a function `Pixel invert()`
 * - implements a constructor with `uint8_t` argument
 * - implements a constructor without arguments
 * - implements a constructor with float argument (percentage of brightness between 0 and 1)
 * - has a static constant NUM_CHANNELS that defines how many channels the pixel has
*/
template<typename Pixel>
class Bitmap {
private:
    const int width;
    const int height;
    Pixel* pixels;
public:
    /**
     * @brief Construct a Bitmap from an FT_Bitmap with pixel mode FT_PIXEL_MODE_GRAY and 256 grays.
    */
    Bitmap(FT_Bitmap& bitmap)
        : width(bitmap.width)
        , height(bitmap.rows)
    {
        switch(bitmap.pixel_mode) {
            case FT_PIXEL_MODE_MONO:
                throw std::invalid_argument("Unsupported pixel mode: FT_PIXEL_MODE_MONO");
            case FT_PIXEL_MODE_GRAY: {
                pixels = new Pixel[width * height];
                uint8_t* buffer = bitmap.buffer;
                if(bitmap.pitch < 0) {
                    buffer += bitmap.pitch * (height - 1);
                }
                for(int i = 0; i < abs(bitmap.pitch) * height; i++) {
                    pixels[i] = Pixel((float)buffer[i] / (bitmap.num_grays - 1));
                }
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
    /**
     * @brief Construct a plain black bitmap with the given dimensions.
    */
    Bitmap(int width, int height) : width(width), height(height) {
        pixels = new Pixel[width * height];
        std::fill_n(pixels, width * height, Pixel());
    }
    /**
     * @brief Copy a Bitmap of another type.
     * @note Works only if Pixel has a constructor with parameter of type OtherPixel.
    */
    template<typename OtherPixel>
    Bitmap(const Bitmap<OtherPixel>& other)
        : width(other.getWidth())
        , height(other.getHeight())
    {
        pixels = new Pixel[width * height];
        for(int i = 0; i < width * height; i++) {
            pixels[i] = Pixel(other.getPixels()[i]);
        }
    }
    ~Bitmap() { delete pixels; }

    /**
     * @brief Get the width of the bitmap.
    */
    int getWidth() const { return width; }
    /**
     * @brief Get the height of the bitmap.
    */
    int getHeight() const { return height; }
    /**
     * @brief Get the pixel array of the bitmap.
    */
    Pixel* getPixels() const { return pixels; }
    /**
     * @brief Get the pixel at the given coordinates.
    */
    Pixel getPixel(int x, int y) const { return pixels[y * width + x]; }

    /**
     * @brief Set the pixel array of the bitmap.
    */
    void setPixels(Pixel* pixels) {
        std::copy(pixels, pixels + width * height, this->pixels);
    }

    /**
     * @brief Set the pixel at the given coordinates.
     * @return Whether the operation was successful.
    */
    bool setPixel(unsigned int x, unsigned int y, const Pixel& pixel) { 
        if(x >= width || y >= height) {
            return false;
        }
        pixels[y * width + x] = pixel; 
        return true;
    }

    /**
     * @brief Overlay another bitmap on top of this one, such that brighter pixels dominate.
     * @param other The bitmap to overlay.
     * @return A new bitmap with the overlay applied.
    */
    Bitmap<Pixel> overlay(const Bitmap<Pixel>& other) const {
        if(width != other.width || height != other.height) {
            throw std::invalid_argument("Bitmaps must have the same dimensions to overlay");
        }
        Bitmap<Pixel> result(width, height);
        for(int i = 0; i < width * height; i++) {
            result.pixels[i] = pixels[i].overlay(other.pixels[i]);
        }
        return result;
    }

    /**
     * @brief Join another bitmap to the bottom of this one.
     * @param other The bitmap to join.
     * @return A new bitmap with the other bitmap joined to the bottom.
    */
    Bitmap<Pixel> joinVertically(const Bitmap<Pixel>& other) const {
        if(width != other.width) {
            throw std::invalid_argument("Bitmaps must have the same width to join");
        }
        Bitmap<Pixel> result(width, height + other.height);
        std::copy(pixels, pixels + width * height, result.pixels);
        //memcpy(result.pixels, pixels, width * height * sizeof(Pixel));
        std::copy(other.pixels, other.pixels + width * height, result.pixels + width * height);
        //memcpy(result.pixels + width * height, other.pixels, width * other.height * sizeof(Pixel));
        return result;
    }

    /**
     * @brief Join another bitmap to the right of this one.
     * @param other The bitmap to join.
     * @return A new bitmap with the other bitmap joined to the right.
    */
    Bitmap<Pixel> joinHorizontally(const Bitmap<Pixel>& other) const {
        if(height != other.height) {
            throw std::invalid_argument("Bitmaps must have the same height to join");
        }
        Bitmap<Pixel> result(width + other.width, height);
        for(int i = 0; i < height; i++) {
            std::copy(pixels + width * i, pixels + width * (i + 1), result.pixels + (width + other.width) * i);
            //memcpy(result.pixels + (width + other.width) * i, pixels + width * i, width * sizeof(Pixel));
            std::copy(other.pixels + other.width * i, other.pixels + other. width * (i + 1), result.pixels + (width + other.width) * i + width);
            //memcpy(result.pixels + (width + other.width) * i + width, other.pixels + other.width * i, other.width * sizeof(Pixel));
        }
        return result;
    }

    /**
     * @brief Place the bitmap on a black canvas with the given dimensions at the given coordinates.
     * @param canvasWidth The width of the canvas.
     * @param canvasHeight The height of the canvas.
     * @param x The x-coordinate to place the bitmap at.
     * @param y The y-coordinate to place the bitmap at.
     * @throws std::invalid_argument If the bitmap does not fit on the canvas.
     * @return A new bitmap with the bitmap placed on the canvas.
    */
    Bitmap<Pixel> placeOnCanvas(int canvasWidth, int canvasHeight, int x, int y) const {
        Bitmap<Pixel> result(canvasWidth, canvasHeight);
        if(x < 0 || y < 0 || x + width > canvasWidth || y + height > canvasHeight) {
            throw std::invalid_argument("Bitmap does not fit on canvas: placing bitmap with dimensions " + std::to_string(width) + "x" + std::to_string(height) + " at (" + std::to_string(x) + ", " + std::to_string(y) + ") on canvas with dimensions " + std::to_string(canvasWidth) + "x" + std::to_string(canvasHeight) + " is out of bounds.");
        }
        for(int i = 0; i < height; i++) {
            std::copy(pixels + width * i, pixels + width * (i + 1), result.pixels + (canvasWidth * (y + i) + x));
            //memcpy(result.pixels + (canvasWidth * (y + i) + x), pixels + width * i, width * sizeof(Pixel));
        }
        return result;
    }

    /**
     * @brief Place the bitmap on a black canvas with the given dimensions, centered.
     * @param canvasWidth The width of the canvas.
     * @param canvasHeight The height of the canvas.
     * @return A new bitmap with the bitmap placed on the canvas.
    */
    Bitmap<Pixel> placeOnCanvas(int canvasWidth, int canvasHeight) const {
        return placeOnCanvas(canvasWidth, canvasHeight, (canvasWidth - width) / 2, (canvasHeight - height) / 2);
    }

    /**
     * @brief Mirror the bitmap horizontally.
     * @return A new bitmap that is mirrored horizontally.
    */
    Bitmap<Pixel> mirror() const {
        Bitmap<Pixel> result(width, height);
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                result.pixels[y * width + x] = pixels[y * width + width-1-x];
            }
        }
        return result;
    }

    /**
     * @brief Rotates this bitmap by 180°.
     * @return A new bitmap that is rotated by 180°.
    */
    Bitmap<Pixel> rotate180() const {
        Bitmap<Pixel> result(width, height);
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                result.pixels[(height-1-y) * width + x] = pixels[y * width + width-1-x];
            }
        }
        return result;
    }

    /**
     * @brief Inverts the pixels of this bitmap.
     * @return A new bitmap with inverted pixels.
    */
    Bitmap<Pixel> invert() const {
        Bitmap<Pixel> result(width, height);
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                result.pixels[y * width + x] = pixels[y * width + x].invert();
            }
        }
        return result;
    }

    /**
     * @brief Print the bitmap to a file.
     * @param filename The name of the file to print to.
     * @return Whether the operation was successful.
    */
    bool printToFile(const char* filename) const {
        int result = stbi_write_png(filename, width, height, Pixel::NUM_CHANNELS, pixels, width * sizeof(Pixel));
        return result != 0;
    }
};

typedef Bitmap<GreyPixel> GreyBitmap;
typedef Bitmap<Grey32Pixel> Grey32Bitmap;
typedef Bitmap<RGB_Pixel> RGB_Bitmap;
typedef Bitmap<RGBA_Pixel> RGBA_Bitmap;

} // namespace rendering

#endif // BITMAP_H
