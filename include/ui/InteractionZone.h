#ifndef INTERACTION_ZONE_H
#define INTERACTION_ZONE_H

#include "Rectangle.h"
#include "Character.h"
#include <functional>

namespace ui {

/**
 * @brief An area on the recipe that can be interacted with.
 * @param InputType The type of the objects that will be used to interact with the recipe.
*/
template<typename InputType>    
class InteractionZone {
private:
    util::IRectangle hitbox, highlight;
    std::function<void(InputType)> interactFunc;
public:
    /**
     * @brief Construct a new Interaction Zone object.
     * @param hitbox The area that can be interacted with.
     * @param highlight The area that will be highlighted when the hitbox is hovered over.
     * @param interactFunc The function that will be executed upon interaction.
    */
    InteractionZone(const util::IRectangle& hitbox, 
                    const util::IRectangle& highlight, 
                    const std::function<void(InputType)>& interactFunc)
        : hitbox(hitbox)
        , highlight(highlight)
        , interactFunc(interactFunc) {}
    /**
     * Interact with this area.
     * @return Whether the stored function has been executed.
    */
    bool interact(InputType inp) const {
        interactFunc(inp);
        return true;
    }
    /**
     * Interact with this area on a given point.
     * @return Whether the stored function has been executed.
    */
    bool interact(util::IPoint p, InputType inp) const {
        if(hitbox.contains(p)) {
            interactFunc(inp);
            return true;
        }
        return false;
    }
    /**
     * Interact with this area on a given point.
     * @return Whether the stored function has been executed.
    */
    bool interact(int x, int y, InputType inp) const {
        return interact(util::IPoint(x,y), inp);
    }
    /**
     * Move the hitbox and highlight area by a given amount.
    */
    void move(int x, int y) {
        hitbox.move(x, y);
        highlight.move(x, y);
    }
    /**
     * Mirror the hitbox and highlight area along a given x-axis.
     * @param axis The x-coordinate of the axis of symmetry.
    */
    void mirrorX(int axis) {
        hitbox.mirrorX(axis);
        highlight.mirrorX(axis);
    }
    /**
     * Mirror the hitbox and highlight area along a given y-axis.
     * @param axis The y-coordinate of the axis of symmetry.
    */
    void mirrorY(int axis) {
        hitbox.mirrorY(axis);
        highlight.mirrorY(axis);
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
    bool interact() const {
        interactFunc();
        return true;
    }
    /**
     * Interact with this area on a given point.
     * @return Whether the stored function has been executed.
    */
    bool interact(util::IPoint p) const {
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
    bool interact(int x, int y) const {
        return interact(util::IPoint(x,y));
    }
    /**
     * Move the hitbox and highlight area by a given amount.
    */
    void move(int x, int y) {
        hitbox.move(x, y);
        highlight.move(x, y);
    }
    /**
     * Mirror the hitbox and highlight area along a given x-axis.
     * @param axis The x-coordinate of the axis of symmetry.
    */
    void mirrorX(int axis) {
        hitbox.mirrorX(axis);
        highlight.mirrorX(axis);
    }
    /**
     * Mirror the hitbox and highlight area along a given y-axis.
     * @param axis The y-coordinate of the axis of symmetry.
    */
    void mirrorY(int axis) {
        hitbox.mirrorY(axis);
        highlight.mirrorY(axis);
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
