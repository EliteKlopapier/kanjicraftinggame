#ifndef INTERACTION_ZONE_H
#define INTERACTION_ZONE_H

#include "Rectangle.h"
#include "Character.h"
#include <functional>

namespace ui {

/**
 * @brief An area on the recipe that can be interacted with.
 * @param T The type of the objects that will be used to interact with the recipe.
*/
template<typename T>    
class InteractionZone {
private:
    util::IRectangle hitbox, highlight;
    std::function<void(T)> interactFunc;
public:
    /**
     * @brief Construct a new Interaction Zone object.
     * @param hitbox The area that can be interacted with.
     * @param highlight The area that will be highlighted when the hitbox is hovered over.
     * @param interactFunc The function that will be executed upon interaction.
    */
    InteractionZone(const util::IRectangle& hitbox, 
                    const util::IRectangle& highlight, 
                    const std::function<void(T)>& interactFunc)
        : hitbox(hitbox)
        , highlight(highlight)
        , interactFunc(interactFunc) {}
    /**
     * Interact with this area.
     * @return Whether the stored function has been executed.
    */
    bool interact(T t) {
        interactFunc(t);
        return true;
    }
    /**
     * Interact with this area on a given point.
     * @return Whether the stored function has been executed.
    */
    bool interact(util::IPoint p, T t) {
        if(hitbox.contains(p)) {
            interactFunc(t);
            return true;
        }
        return false;
    }
    /**
     * Interact with this area on a given point.
     * @return Whether the stored function has been executed.
    */
    bool interact(int x, int y, T t) {
        return interact(util::IPoint(x,y), t);
    }
    /**
     * @return The area that will be highlighted when the hitbox is hovered over.
    */
    const util::IRectangle& getHighlight() const { return highlight; }
    /**
     * @return The area that can be interacted with.
    */
    const util::IRectangle& getHitbox() const { return hitbox; }
};

/**
 * @brief An area on the recipe that can be interacted with.
*/
template<>
class InteractionZone<void> {
private:
    util::IRectangle hitbox, highlight;
    std::function<void()> interactFunc;
public:
    /**
     * @brief Construct a new Interaction Zone object.
     * @param hitbox The area that can be interacted with.
     * @param highlight The area that will be highlighted when the hitbox is hovered over.
     * @param interactFunc The function that will be executed upon interaction.
    */
    InteractionZone(const util::IRectangle& hitbox, 
                    const util::IRectangle& highlight, 
                    const std::function<void()>& interactFunc)
        : hitbox(hitbox)
        , highlight(highlight)
        , interactFunc(interactFunc) {}
    /**
     * Interact with this area.
     * @return Whether the stored function has been executed.
    */
    bool interact() {
        interactFunc();
        return true;
    }
    /**
     * Interact with this area on a given point.
     * @return Whether the stored function has been executed.
    */
    bool interact(util::IPoint p) {
        if(hitbox.contains(p)) {
            interactFunc();
            return true;
        }
        return false;
    }
    /**
     * Interact with this area on a given point.
     * @return Whether the stored function has been executed.
    */
    bool interact(int x, int y) {
        return interact(util::IPoint(x,y));
    }
    /**
     * @return The area that will be highlighted when the hitbox is hovered over.
    */
    const util::IRectangle& getHighlight() const { return highlight; }
    /**
     * @return The area that can be interacted with.
    */
    const util::IRectangle& getHitbox() const { return hitbox; } 
};

} // namespace ui

#endif // INTERACTION_ZONE_H
