
#ifndef PLAYER_STATS_H
#define PLAYER_STATS_H

#include <string>

namespace player {

enum Stats {
    MAX_HEALTH,
    MAX_INK,
    ARMOR
};

/**
 * @brief Gives a string representation of a stat.
*/
extern std::string statToString(Stats stat);

} // namespace player

#endif // PLAYER_STATS_H

