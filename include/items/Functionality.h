
#ifndef FUNCTIONALITY_H
#define FUNCTIONALITY_H

#include <string>

namespace crafting {
    class Character;
}

namespace items {

/**
 * @brief An interface for a functionality that an item can have.
*/
class Functionality {
protected:
    // The character that has this functionality.
    crafting::Character* owner;
public:
    /**
     * @brief Returns a description of the functionality.
    */
    virtual std::string getDescription() const = 0;

    Functionality(crafting::Character* owner)
        : owner(owner)
    { }
};

} // namespace items

#endif // FUNCTIONALITY_H
