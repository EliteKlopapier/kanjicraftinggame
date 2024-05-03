#ifndef INTERACTION_MAP_H
#define INTERACTION_MAP_H

#include "InteractionZone.h"
#include <stdexcept>
#include <vector>

namespace ui {

/**
 * @brief A 2D map of zones on a recipe to interact with.
 * @param InputType The type of object carried by the mouse when interacting.
*/
template<typename InputType>
class InteractionMap {
private:
    // The RGBA value with which to highlight
    static constexpr rendering::RGBA_Pixel HIGHLIGHTING = rendering::RGBA_Pixel(0,0,200,50);
    std::vector<InteractionZone<InputType>> zones;
    int width, height;
public:
    /**
     * Create an empty InteractionMap with the given dimensions.
    */
    InteractionMap(int width, int height)
        : width(width)
        , height(height) {}

    int getWidth() { return width; }
    int getHeight() { return height; }

    /**
     * Add a zone to the map.
     * @param hitbox The area that can be interacted with. Coordinates are relative to the top left corner of the map.
     * @param highlight The area to highlight when the mouse hovers over the hitbox. Coordinates are relative to the top left corner of the map.
     * @param interactFunc The function to call when the zone is interacted with.
    */
    void addZone(const geometry::IRectangle& hitbox, 
                 const geometry::IRectangle& highlight, 
                 const std::function<void(InputType)>& interactFunc) {
        /*for(const InteractionZone<InputType>& zone : zones) {
            if(zone.getHitbox().intersects(hitbox)) {
                throw std::invalid_argument("Overlapping hitboxes in InteractionMap!");
            }
        }*/
        zones.emplace_back(hitbox, highlight, interactFunc);
    }

    /**
     * Add a zone to the map.
     * @param zone The zone to add.
    */
    void addZone(const InteractionZone<InputType>& zone) {
        zones.emplace_back(zone);
    }

    /**
     * @brief Renders the InteractionMap with the are highlighted depending on the mouse's position.
     * @param mouseX The x-coordinate of the mouse relative to the top left corner of the map.
     * @param mouseY The y-coordinate of the mouse relative to the top left corner of the map.
    */
    rendering::RGBA_Bitmap render(int mouseX, int mouseY) const {
        rendering::RGBA_Bitmap result(width, height);
        if(mouseX < 0 || mouseY < 0 || mouseX >= width || mouseY >= height) {
            return result;
        }
        for(const InteractionZone<InputType>& zone : zones) {
            if(zone.getHitbox().contains(geometry::IVec2(mouseX, mouseY))) {
                geometry::IVec2 from = zone.getHighlight().getFrom();
                geometry::IVec2 to = zone.getHighlight().getTo();
                for(int x = from.x; x < to.x; x++) {
                    for(int y = from.y; y < to.y; y++) {
                        result.setPixel(x, y, HIGHLIGHTING);
                    }
                }
                break;
            }
        }
        return result;
    }

    /**
     * @brief Interact with the zone at the given coordinates.
     * @param mouseX The x-coordinate of the mouse relative to the top left corner of the map.
     * @param mouseY The y-coordinate of the mouse relative to the top left corner of the map.
     * @param input The object carried by the mouse.
    */
    bool interact(int mouseX, int mouseY, InputType input) {
        if(mouseX < 0 || mouseY < 0 || mouseX >= width || mouseY >= height) {
            return false;
        }
        for(const InteractionZone<InputType>& zone : zones) {
            if(zone.hitbox.contains(geometry::IVec2(mouseX, mouseY))) {
                return zone.interact(input);
            }
        }
        return false;
    }

    /**
     * @brief Join this InteractionMap with another horizontally.
     * @param other The InteractionMap to join with.
     * @throws std::invalid_argument If the InteractionMaps do not have the same height.
     * @return A new InteractionMap with the zones of both maps.
    */
    InteractionMap<InputType> joinHorizontally(const InteractionMap<InputType>& other) {
        if(height != other.height) {
            throw std::invalid_argument("InteractionMaps must have the same height to be joined.");
        }
        InteractionMap<InputType> result(width + other.width, height);
        for(const InteractionZone<InputType>& zone : zones) {
            result.addZone(zone);
        }
        for(InteractionZone<InputType> zone : other.zones) {
            zone.move(width, 0);
            result.addZone(zone);
        }
        return result;
    }

    /**
     * @brief Join this InteractionMap with another vertically.
     * @param other The InteractionMap to join with.
     * @throws std::invalid_argument If the InteractionMaps do not have the same width.
     * @return A new InteractionMap with the zones of both maps.
    */
    InteractionMap<InputType> joinVertically(const InteractionMap<InputType>& other) {
        if(width != other.width) {
            throw std::invalid_argument("InteractionMaps must have the same width to be joined.");
        }
        InteractionMap<InputType> result(width, height + other.height);
        for(const InteractionZone<InputType>& zone : zones) {
            result.addZone(zone);
        }
        for(InteractionZone<InputType> zone : other.zones) {
            zone.move(0, height);
            result.addZone(zone);
        }
        return result;
    }

    /**
     * @brief Overlay another InteractionMap on top of this one.
     * @param other The InteractionMap to overlay.
     * @throws std::invalid_argument If the InteractionMaps do not have the same dimensions.
     * @return A new InteractionMap with the zones of both maps.
    */
    InteractionMap<InputType> overlay(const InteractionMap<InputType>& other) {
        if(width != other.width || height != other.height) {
            throw std::invalid_argument("InteractionMaps must have the same dimensions to be overlaid.");
        }
        InteractionMap<InputType> result(width, height);
        for(const InteractionZone<InputType>& zone : other.zones) {
            result.addZone(zone);
        }
        for(const InteractionZone<InputType>& zone : zones) {
            result.addZone(zone);
        }
        return result;
    }

    /**
     * @brief Place the InteractionMap on a canvas with the given dimensions at the given coordinates.
     * @param canvasWidth The width of the canvas.
     * @param canvasHeight The height of the canvas.
     * @param x The x-coordinate of the top left corner of the InteractionMap on the canvas.
     * @param y The y-coordinate of the top left corner of the InteractionMap on the canvas.
     * @throws std::invalid_argument If the InteractionMap does not fit on the canvas.
     * @return A new InteractionMap placed on the canvas.
    */
    InteractionMap<InputType> placeOnCanvas(int canvasWidth, int canvasHeight, int x, int y) {
        if(x < 0 || y < 0 || x + width > canvasWidth || y + height > canvasHeight) {
            throw std::invalid_argument("InteractionMap does not fit on canvas.");
        }
        InteractionMap<InputType> result(canvasWidth, canvasHeight);
        for(InteractionZone<InputType> zone : zones) {
            zone.move(x, y);
            result.addZone(zone);
        }
        return result;
    }

    /**
     * @brief Place the InteractionMap on a canvas with the given dimensions, centered.
     * @param canvasWidth The width of the canvas.
     * @param canvasHeight The height of the canvas.
     * @throws std::invalid_argument If the InteractionMap does not fit on the canvas.
     * @return A new InteractionMap placed on the canvas.
    */
    InteractionMap<InputType> placeOnCanvas(int canvasWidth, int canvasHeight) {
        return placeOnCanvas(canvasWidth, canvasHeight, (canvasWidth - width) / 2, (canvasHeight - height) / 2);
    }

    /**
     * @brief Mirror the InteractionMap horizontally.
     * @return A new InteractionMap with the zones mirrored.
    */
    InteractionMap<InputType> mirror() {
        InteractionMap<InputType> result(width, height);
        for(InteractionZone<InputType> zone : zones) {
            zone.mirrorX(width / 2);
            if(!(width % 2)) {
                zone.move(-1, 0);
            }
            result.addZone(zone);
        }
        return result;
    }

    /**
     * @brief Rotate the InteractionMap 180 degrees.
     * @return A new InteractionMap with the zones rotated.
    */
    InteractionMap<InputType> rotate180() {
        InteractionMap<InputType> result(width, height);
        for(InteractionZone<InputType> zone : zones) {
            zone.mirrorX(width / 2);
            if(!(width % 2)) {
                zone.move(-1, 0);
            }
            zone.mirrorY(height / 2);
            if(!(height % 2)) {
                zone.move(0, -1);
            }
            result.addZone(zone);
        }
        return result;
    }
};

/**
 * @brief A 2D map of zones on a recipe to interact with with no input object.
*/
template<>
class InteractionMap<void> {
private:
    // The RGBA value with which to highlight
    static constexpr rendering::RGBA_Pixel HIGHLIGHTING = rendering::RGBA_Pixel(0,0,200,50);
    std::vector<InteractionZone<void>> zones;
    int width, height;
public:
    /**
     * Create an empty InteractionMap with the given dimensions.
    */
    InteractionMap(int width, int height)
        : width(width)
        , height(height) {}

    int getWidth() { return width; }
    int getHeight() { return height; }

    /**
     * Add a zone to the map.
     * @param hitbox The area that can be interacted with. Coordinates are relative to the top left corner of the map.
     * @param highlight The area to highlight when the mouse hovers over the hitbox. Coordinates are relative to the top left corner of the map.
     * @param interactFunc The function to call when the zone is interacted with.
    */
    void addZone(const geometry::IRectangle& hitbox, 
                 const geometry::IRectangle& highlight, 
                 const std::function<void()>& interactFunc) {
        /*for(const InteractionZone<void>& zone : zones) {
            if(zone.getHitbox().intersects(hitbox)) {
                throw std::invalid_argument("Overlapping hitboxes in InteractionMap!");
            }
        }*/
        zones.emplace_back(hitbox, highlight, interactFunc);
    }

    /**
     * Add a zone to the map.
     * @param zone The zone to add.
    */
    void addZone(const InteractionZone<void> zone) {
        zones.emplace_back(zone);
    }

    /**
     * @brief Renders the InteractionMap with the are highlighted depending on the mouse's position.
     * @param mouseX The x-coordinate of the mouse relative to the top left corner of the map.
     * @param mouseY The y-coordinate of the mouse relative to the top left corner of the map.
    */
    rendering::RGBA_Bitmap render(int mouseX, int mouseY) const {
        rendering::RGBA_Bitmap result(width, height);
        if(mouseX < 0 || mouseY < 0 || mouseX >= width || mouseY >= height) {
            return result;
        }
        for(const InteractionZone<void>& zone : zones) {
            if(zone.getHitbox().contains(geometry::IVec2(mouseX, mouseY))) {
                geometry::IVec2 from = zone.getHighlight().getFrom();
                geometry::IVec2 to = zone.getHighlight().getTo();
                for(int x = from.x; x < to.x; x++) {
                    for(int y = from.y; y < to.y; y++) {
                        result.setPixel(x, y, HIGHLIGHTING);
                    }
                }
                break;
            }
        }
        return result;
    }

    /**
     * @brief Interact with the zone at the given coordinates.
     * @param mouseX The x-coordinate of the mouse relative to the top left corner of the map.
     * @param mouseY The y-coordinate of the mouse relative to the top left corner of the map.
    */
    bool interact(int mouseX, int mouseY) {
        if(mouseX < 0 || mouseY < 0 || mouseX >= width || mouseY >= height) {
            return false;
        }
        for(const InteractionZone<void>& zone : zones) {
            if(zone.getHitbox().contains(geometry::IVec2(mouseX, mouseY))) {
                return zone.interact();
            }
        }
        return false;
    }

    /**
     * @brief Join this InteractionMap with another horizontally.
     * @param other The InteractionMap to join with.
     * @throws std::invalid_argument If the InteractionMaps do not have the same height.
     * @return A new InteractionMap with the zones of both maps.
    */
    InteractionMap<void> joinHorizontally(const InteractionMap<void>& other) {
        if(height != other.height) {
            throw std::invalid_argument("InteractionMaps must have the same height to be joined.");
        }
        InteractionMap<void> result(width + other.width, height);
        for(const InteractionZone<void>& zone : zones) {
            result.addZone(zone);
        }
        for(InteractionZone<void> zone : other.zones) {
            zone.move(width, 0);
            result.addZone(zone);
        }
        return result;
    }

    /**
     * @brief Join this InteractionMap with another vertically.
     * @param other The InteractionMap to join with.
     * @throws std::invalid_argument If the InteractionMaps do not have the same width.
     * @return A new InteractionMap with the zones of both maps.
    */
    InteractionMap<void> joinVertically(const InteractionMap<void>& other) {
        if(width != other.width) {
            throw std::invalid_argument("InteractionMaps must have the same width to be joined.");
        }
        InteractionMap<void> result(width, height + other.height);
        for(const InteractionZone<void>& zone : zones) {
            result.addZone(zone);
        }
        for(InteractionZone<void> zone : other.zones) {
            zone.move(0, height);
            result.addZone(zone);
        }
        return result;
    }

    /**
     * @brief Overlay another InteractionMap on top of this one.
     * @param other The InteractionMap to overlay.
     * @throws std::invalid_argument If the InteractionMaps do not have the same dimensions.
     * @return A new InteractionMap with the zones of both maps.
    */
    InteractionMap<void> overlay(const InteractionMap<void>& other) {
        if(width != other.width || height != other.height) {
            throw std::invalid_argument("InteractionMaps must have the same dimensions to be overlaid.");
        }
        InteractionMap<void> result(width, height);
        for(const InteractionZone<void>& zone : other.zones) {
            result.addZone(zone);
        }
        for(const InteractionZone<void>& zone : zones) {
            result.addZone(zone);
        }
        return result;
    }

    /**
     * @brief Place the InteractionMap on a canvas with the given dimensions at the given coordinates.
     * @param canvasWidth The width of the canvas.
     * @param canvasHeight The height of the canvas.
     * @param x The x-coordinate of the top left corner of the InteractionMap on the canvas.
     * @param y The y-coordinate of the top left corner of the InteractionMap on the canvas.
     * @throws std::invalid_argument If the InteractionMap does not fit on the canvas.
     * @return A new InteractionMap placed on the canvas.
    */
    InteractionMap<void> placeOnCanvas(int canvasWidth, int canvasHeight, int x, int y) {
        if(x < 0 || y < 0 || x + width > canvasWidth || y + height > canvasHeight) {
            throw std::invalid_argument("InteractionMap does not fit on canvas.");
        }
        InteractionMap<void> result(canvasWidth, canvasHeight);
        for(InteractionZone<void> zone : zones) {
            zone.move(x, y);
            result.addZone(zone);
        }
        return result;
    }

    /**
     * @brief Place the InteractionMap on a canvas with the given dimensions, centered.
     * @param canvasWidth The width of the canvas.
     * @param canvasHeight The height of the canvas.
     * @throws std::invalid_argument If the InteractionMap does not fit on the canvas.
     * @return A new InteractionMap placed on the canvas.
    */
    InteractionMap<void> placeOnCanvas(int canvasWidth, int canvasHeight) {
        return placeOnCanvas(canvasWidth, canvasHeight, (canvasWidth - width) / 2, (canvasHeight - height) / 2);
    }

    /**
     * @brief Mirror the InteractionMap horizontally.
     * @return A new InteractionMap with the zones mirrored.
    */
    InteractionMap<void> mirror() {
        InteractionMap<void> result(width, height);
        for(InteractionZone<void> zone : zones) {
            zone.mirrorX(width / 2);
            if(!(width % 2)) {
                zone.move(-1, 0);
            }
            result.addZone(zone);
        }
        return result;
    }

    /**
     * @brief Rotate the InteractionMap 180 degrees.
     * @return A new InteractionMap with the zones rotated.
    */
    InteractionMap<void> rotate180() {
        InteractionMap<void> result(width, height);
        for(InteractionZone<void> zone : zones) {
            zone.mirrorX(width / 2);
            if(!(width % 2)) {
                zone.move(-1, 0);
            }
            zone.mirrorY(height / 2);
            if(!(height % 2)) {
                zone.move(0, -1);
            }
            result.addZone(zone);
        }
        return result;
    }
};

} // namespace ui

#endif // INTERACTION_MAP_H
