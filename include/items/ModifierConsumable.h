
#ifndef MODIFIER_CONSUMABLE_H
#define MODIFIER_CONSUMABLE_H

#include "Consumable.h"
#include "stringUtil.h"
#include "TimedModifier.h"

namespace items {

class ModifierConsumable : public Consumable {
private:
    player::Modifier modifier;
public:
    ModifierConsumable(crafting::Character* owner, const player::Modifier& modifier)
        : Consumable(owner)
        , modifier(modifier)
    { }

    ModifierConsumable(crafting::Character* owner, player::Stats stat, int value)
        : Consumable(owner)
        , modifier("Consumed " + util::u32_to_u8(std::u32string(1, owner->getCharacter())), stat, value)
    { }

    ModifierConsumable(crafting::Character* owner, player::Stats stat, int value, unsigned int duration)
        : Consumable(owner)
        , modifier(player::TimedModifier("Consumed " + util::u32_to_u8(std::u32string(1, owner->getCharacter())), stat, value, duration)) 
    { }
    
    void onConsume(player::Player* consumer) override {
        consumer->addModifier(modifier);
    }
    
    std::string getConsumeDescription() const override {
        return "add the modifier \"" 
             + modifier.getName() 
             + "\" to the player, which changes " 
             + player::statToString(modifier.getStat()) 
             + " by " 
             + std::to_string(modifier.getValue()) 
             + ".";
    }
};

} // namespace items

#endif // MODIFIER_CONSUMABLE_H
