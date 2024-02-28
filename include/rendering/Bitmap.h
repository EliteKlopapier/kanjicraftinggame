#ifndef BITMAP_H
#define BITMAP_H

#include "freeTypeStuff.h"
#include FT_BITMAP_H
#include <cstdint>

namespace rendering {

/**
 * @brief A greyscale bitmap with one byte per pixel and a few utility functions.
*/
class Bitmap {
private:
    const int width;
    const int height;
    uint8_t* pixels;
public:
    /**
     * @brief Construct a Bitmap from an FT_Bitmap with pixel mode FT_PIXEL_MODE_GRAY and 256 grays.
    */
    Bitmap(FT_Bitmap& bitmap);
    /**
     * @brief Construct a plain black bitmap with the given dimensions.
    */
    Bitmap(int width, int height);
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
    uint8_t* getPixels() const { return pixels; }
    /**
     * @brief Get the pixel at the given coordinates.
    */
    uint8_t getPixel(int x, int y) const { return pixels[y * width + x]; }

    /**
     * @brief Set the pixel array of the bitmap.
    */
    void setPixels(uint8_t* pixels) { this->pixels = pixels; }

    /**
     * @brief Overlay another bitmap on top of this one, such that brighter pixels dominate.
     * @param other The bitmap to overlay.
     * @return A new bitmap with the overlay applied.
    */
    Bitmap overlay(const Bitmap& other) const;

    /**
     * @brief Join another bitmap to the bottom of this one.
     * @param other The bitmap to join.
     * @return A new bitmap with the other bitmap joined to the bottom.
    */
    Bitmap joinVertically(const Bitmap& other) const;

    /**
     * @brief Join another bitmap to the right of this one.
     * @param other The bitmap to join.
     * @return A new bitmap with the other bitmap joined to the right.
    */
    Bitmap joinHorizontally(const Bitmap& other) const;

    /**
     * @brief Place the bitmap on a black canvas with the given dimensions at the given coordinates.
     * @param canvasWidth The width of the canvas.
     * @param canvasHeight The height of the canvas.
     * @param x The x-coordinate to place the bitmap at.
     * @param y The y-coordinate to place the bitmap at.
     * @return A new bitmap with the bitmap placed on the canvas.
    */
    Bitmap placeOnCanvas(int canvasWidth, int canvasHeight, int x, int y) const;

    /**
     * @brief Place the bitmap on a black canvas with the given dimensions, centered.
     * @param canvasWidth The width of the canvas.
     * @param canvasHeight The height of the canvas.
     * @return A new bitmap with the bitmap placed on the canvas.
    */
    Bitmap placeOnCanvas(int canvasWidth, int canvasHeight) const; 

    /**
     * @brief Mirror the bitmap horizontally.
     * @return A new bitmap that is mirrored horizontally.
    */
    Bitmap mirror() const;

    /**
     * @brief Rotates this bitmap by 180°.
    */
    Bitmap rotate180() const;

    /**
     * @brief Print the bitmap to a file.
     * @param filename The name of the file to print to.
     * @return Whether the operation was successful.
    */
    bool printToFile(const char* filename) const;
};

} // namespace rendering

#endif // BITMAP_H
