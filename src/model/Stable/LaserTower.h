#ifndef WARP_LASERTOWER_H
#define WARP_LASERTOWER_H

#include <memory>

#include "Stable.h"
#include "../Constants.h"

class LaserTower : public Stable{
public:
    LaserTower(Coordinate position, const std::shared_ptr<FieldEntityCallbackClass> &gameModelCallback)
            : Stable(position, gameModelCallback) {
        this->upgraded = false;
        this->hp = CONSTANTS::LASERTOWER_MAX_HP;
    }

    int maxHp() override { return CONSTANTS::LASERTOWER_MAX_HP; }
    int cost() override { return CONSTANTS::LASERTOWER_BASE_COST; }
    int upgradeCost() override { return CONSTANTS::LASERTOWER_UPGRADE_COST; }
    int attackSpeed() override { return !upgraded ?
                                        CONSTANTS::LASERTOWER_BASE_ATTACKSPEED : CONSTANTS::LASERTOWER_UPGRADE_ATTACKSPEED; }
    int damage() override { return !upgraded ?
                                   CONSTANTS::LASERTOWER_BASE_DAMAGE : CONSTANTS::LASERTOWER_UPGRADE_DAMAGE;}

    void doActions() override {
        if(timeCounter % attackSpeed() == 0){
            attack();
        }
    }
    int removeValue() override { return !upgraded ?
                                       CONSTANTS::LASERTOWER_BASE_REMOVE_VALUE : CONSTANTS::LASERTOWER_UPGRADE_REMOVE_VALUE; }
    // void getStats() override;
};


#endif //WARP_LASERTOWER_H
