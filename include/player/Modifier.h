
#ifndef PLAYER_MODIFIER_H
#define PLAYER_MODIFIER_H

#include "Stats.h"
#include <string>

namespace player {

/**
 * @brief A modifier that affects a stat of a player. This is the base implementation where the change is permanent unless manually removed.
*/
class Modifier {
private:
    std::string name;
    Stats stat;
    int value;
public:
    Modifier(const std::string& name, Stats stat, int value)
        : name(name)
        , stat(stat)
        , value(value)
    { }

    /**
     * @brief Returns the name or source of the modifier.
    */
    std::string getName() const {
        return name;
    }

    /**
     * @brief Returns the stat that the modifier affects.
    */
    Stats getStat() const {
        return stat;
    }

    /**
     * @brief Returns the value by which the stat is modified.
    */
    int getValue() const {
        return value;
    }

    virtual bool isActive() const {
        return true;
    }
};

}

#endif // PLAYER_MODIFIER_H
