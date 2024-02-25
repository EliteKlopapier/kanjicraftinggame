#ifndef TIMEDMODIFIER_H
#define TIMEDMODIFIER_H

#include "Modifier.h"
#include <chrono>

namespace player {

/**
 * @brief A modifier that affects a stat of a player. This is a timed implementation where the change is temporary and will expire after a certain duration.
*/
class TimedModifier : public Modifier {
private:
    const std::chrono::time_point<std::chrono::steady_clock> endTime;
public:
    TimedModifier(const std::string& name, Stats stat, int value, unsigned int duration)
        : Modifier(name, stat, value)
        , endTime(std::chrono::steady_clock::now() + std::chrono::seconds(duration))
    { }

    const std::chrono::time_point<std::chrono::steady_clock>& getEndTime() const {
        return endTime;
    }

    bool isActive() const override {
        return std::chrono::steady_clock::now() < endTime;
    }
};

} // namespace player

#endif // TIMEDMODIFIER_H
