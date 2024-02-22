
#ifndef PLAYER_MODIFIER_H
#define PLAYER_MODIFIER_H

#include "Stats.h"
#include <string>

namespace player {

struct Modifier {
    // The name or source of the modifier.
    std::string name;
    // The stat that the modifier affects.
    Stats stat;
    // The value by which the stat is modified.
    int value;

    Modifier(const std::string& name, Stats stat, int value)
        : name(name)
        , stat(stat)
        , value(value)
    { }
};

}

#endif // PLAYER_MODIFIER_H
