#ifndef WARP_SNIPERTOWER_H
#define WARP_SNIPERTOWER_H

#include <memory>

#include "Stable.h"
#include "../Constants.h"

class SniperTower : public Stable{
public:
    SniperTower(Coordinate position,
        const std::shared_ptr<FieldEntityCallbackClass>& gameModelCallback) :
            Stable(position, gameModelCallback){
        this->upgraded = false;
        this->hp = CONSTANTS::SNIPERTOWER_MAX_HP;
    }

    int maxHp() override { return CONSTANTS::SNIPERTOWER_MAX_HP; }
    int cost() override { return CONSTANTS::SNIPERTOWER_BASE_COST; }
    int upgradeCost() override { return CONSTANTS::SNIPERTOWER_UPGRADE_COST; }
    int attackSpeed() override { return !upgraded?
                                 CONSTANTS::SNIPERTOWER_BASE_ATTACKSPEED : CONSTANTS::SNIPERTOWER_UPGRADE_ATTACKSPEED; }
    int damage() override { return !upgraded?
                                  CONSTANTS::SNIPERTOWER_BASE_DAMAGE : CONSTANTS::SNIPERTOWER_UPGRADE_DAMAGE; }

    void doActions() override {
        if(timeCounter % attackSpeed() == 0){
            attack();
        }
    }
    int removeValue() override {return !upgraded?
                                       CONSTANTS::SNIPERTOWER_BASE_REMOVE_VALUE : CONSTANTS::SNIPERTOWER_UPGRADE_REMOVE_VALUE;}
    // void getStats() override;
};


#endif //WARP_SNIPERTOWER_H
