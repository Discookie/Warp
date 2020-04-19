#ifndef WARP_HQDEFENSE_H
#define WARP_HQDEFENSE_H

#include <memory>

#include "Hq.h"
#include "../Constants.h"

class HqDefense : public Hq {
public:
    HqDefense(Coordinate position,
        const std::shared_ptr<FieldEntityCallbackClass>& gameModelCallback) :
            Hq(position, gameModelCallback){
        this->hp = CONSTANTS::HQDEFENSE_MAX_HP;
    }

    int maxHp() override { return CONSTANTS::HQDEFENSE_MAX_HP; }
    int cost() override { return  CONSTANTS::HQDEFENSE_BASE_COST; }
    int upgradeCost() override { return CONSTANTS::HQDEFENSE_UPGRADE_COST; }
    int attackSpeed() override { return CONSTANTS::HQDEFENSE_ATTACKSPEED; }
    int damage() override { return CONSTANTS::HQDEFENSE_DAMAGE; }
    void doActions() override{
        if(timeCounter % attackSpeed() == 0){
            attack();
        }
    }

    int removeValue() override { return CONSTANTS::HQDEFENSE_REMOVE_VALUE; }
    // void getStats() override;
};


#endif //WARP_HQDEFENSE_H
