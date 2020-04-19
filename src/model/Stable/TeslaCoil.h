#ifndef WARP_TESLACOIL_H
#define WARP_TESLACOIL_H

#include <memory>

#include "Stable.h"
#include "../Constants.h"

class TeslaCoil : public Stable{
public:
    TeslaCoil(Coordinate position,
              const std::shared_ptr<FieldEntityCallbackClass>& gameModelCallback) :
            Stable(position, gameModelCallback){
        this->upgraded = false;
        this->hp = CONSTANTS::TESLACOIL_MAX_HP;
    }

    int maxHp() override { return CONSTANTS::TESLACOIL_MAX_HP; }
    int cost() override { return CONSTANTS::TESLACOIL_BASE_COST; }
    int upgradeCost() override { return CONSTANTS::TESLACOIL_UPGRADE_COST; }
    int attackSpeed() override { return !upgraded ?
                                        CONSTANTS::TESLACOIL_BASE_ATTACKSPEED : CONSTANTS::TESLACOIL_UPGRADE_ATTACKSPEED; }
    int damage() override { return !upgraded ?
                                   CONSTANTS::TESLACOIL_BASE_DAMAGE : CONSTANTS::TESLACOIL_UPGRADE_DAMAGE; }
    void doActions() override {
        if(timeCounter % attackSpeed() == 0){
            attack();
        }
    }

    int removeValue() override {return !upgraded ?
                                       CONSTANTS::TESLACOIL_BASE_REMOVE_VALUE: CONSTANTS::TESLACOIL_UPGRADE_REMOVE_VALUE;}
    // void getStats() override;
};


#endif //WARP_TESLACOIL_H
