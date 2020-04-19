#ifndef WARP_SPECIAL_H
#define WARP_SPECIAL_H

#include <memory>

#include "Stable.h"
#include "../Constants.h"

class Special : public Stable{
public:
    Special(Coordinate position,
        const std::shared_ptr<FieldEntityCallbackClass>& gameModelCallback) :
            Stable(position, gameModelCallback) {
        this->upgraded = true;
        this->hp = CONSTANTS::SPECIAL_MAX_HP;
    }

    int maxHp() override { return CONSTANTS::SPECIAL_MAX_HP; }
    int cost() override { return CONSTANTS::SPECIAL_BASE_COST; }
    int upgradeCost() override { return CONSTANTS::SPECIAL_UPGRADE_COST; }
    int attackSpeed() override { return CONSTANTS::SPECIAL_ATTACKSPEED; }
    int damage() override { return CONSTANTS::SPECIAL_DAMAGE; }

    void doActions() override {
        if(timeCounter % attackSpeed() == 0){
            attack();
            die();
        }
    }
    int removeValue() override { return CONSTANTS::SPECIAL_REMOVE_VALUE; }
    void takeDamage(int amount) override {}
    // void getStats() override;
};


#endif //WARP_SPECIAL_H
