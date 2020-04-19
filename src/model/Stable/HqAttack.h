#ifndef WARP_HQATTACK_H
#define WARP_HQATTACK_H

#include <memory>

#include "Hq.h"
#include "../Constants.h"

class HqAttack : public Hq {
public:
    HqAttack(Coordinate position,
        const std::shared_ptr<FieldEntityCallbackClass>& gameModelCallback) :
            Hq(position, gameModelCallback) {
            this->hp = CONSTANTS::HQATTACK_MAX_HP;
    }

    int maxHp() override { return CONSTANTS::HQATTACK_MAX_HP; }
    int cost() override { return CONSTANTS::HQATTACK_BASE_COST; }
    int upgradeCost() override { return CONSTANTS::HQATTACK_UPGRADE_COST; }
    int attackSpeed() override { return CONSTANTS::HQATTACK_ATTACKSPEED; }
    int damage() override { return CONSTANTS::HQATTACK_DAMAGE; }

    void doActions() override {
        if(timeCounter % attackSpeed() == 0){
            attack();
        }
    }
    int removeValue() override { return CONSTANTS::HQATTACK_REMOVE_VALUE; }
    // void getStats() override;
};


#endif //WARP_HQATTACK_H
