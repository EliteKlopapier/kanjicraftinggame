#include "Stats.h"

namespace player {

std::string statToString(Stats stat) {
    switch (stat) {
        case Stats::MAX_HEALTH:
            return "Max Health";
        case Stats::MAX_INK:
            return "Max Ink";
        case Stats::ARMOR:
            return "Armor";
        default:
            return "Unknown";
    }
}

} // namespace player
