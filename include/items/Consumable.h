#ifndef CONSUMABLE_H
#define CONSUMABLE_H

#include "Functionality.h"
#include "Player.h"
#include "Modifier.h"

namespace items {

/**
 * @brief An interface for an item that can be consumed by a player.
*/
class Consumable : public Functionality {
public:
    /**
     * @brief Called when the item is consumed by a player.
     * @param consumer The player that consumed the item.
    */
    virtual void onConsume(player::Player* consumer) = 0;
    /**
     * @brief Returns a description of what happens when the item is consumed. Should extend the sentence "Can be consumed to...".
    */
    virtual std::string getConsumeDescription() const = 0;
    
    std::string getDescription() const override {
        return "Can be consumed to " + getConsumeDescription();
    }

    Consumable(crafting::Character* owner)
        : Functionality(owner)
    { }
};

/**
 * @brief The functionality that makes an item heal or damage a player when consumed.
*/
class HealthConsumable : public Consumable {
private:
    int healAmount;
public:
    HealthConsumable(int healAmount)
        : healAmount(healAmount)
        , Consumable(nullptr)
    { }
    
    void onConsume(player::Player* consumer) override {
        consumer->changeHealth(healAmount);
    }
    
    std::string getConsumeDescription() const override {
        return (healAmount >= 0 ? "heal " : "take ") + std::to_string(healAmount) + (healAmount >= 0 ? " health." : "damage.");
    }
};

/**
 * @brief The functionality that makes an item give or take gold from a player when consumed.
*/
class GoldConsumable : public Consumable {
private:
    int goldAmount;
public:
    GoldConsumable(int goldAmount)
        : goldAmount(goldAmount)
        , Consumable(nullptr)
    { }
    
    void onConsume(player::Player* consumer) override {
        consumer->changeGold(goldAmount);
    }
    
    std::string getConsumeDescription() const override {
        return (goldAmount >= 0 ? "gain " : "lose ") + std::to_string(goldAmount) + " gold.";
    }

};

/**
 * @brief The functionality that makes an item give or take ink from a player when consumed.
*/
class InkConsumable : public Consumable {
private:
    int inkAmount;
public:
    InkConsumable(int inkAmount)
        : inkAmount(inkAmount)
        , Consumable(nullptr)
    { }
    
    void onConsume(player::Player* consumer) override {
        consumer->changeInk(inkAmount);
    }
    
    std::string getConsumeDescription() const override {
        return (inkAmount >= 0 ? "gain " : "lose ") + std::to_string(inkAmount) + " ink.";
    }

};

} // namespace items

#endif // CONSUMABLE_H
