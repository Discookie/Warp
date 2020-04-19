#ifndef WARP_FACTORY_H
#define WARP_FACTORY_H

#include <memory>

#include "Stable.h"
#include "../Constants.h"

class Factory : public Stable {
public:
    Factory(Coordinate position,
        const std::shared_ptr<FieldEntityCallbackClass>& gameModelCallback) :
        Stable(position, gameModelCallback){
            this->upgraded = false;
            this->hp = CONSTANTS::FACTORY_MAX_HP;
    }

    int maxHp() override { return CONSTANTS::FACTORY_MAX_HP; }
    int cost()  override { return CONSTANTS::FACTORY_BASE_COST; }
    int upgradeCost() override { return CONSTANTS::FACTORY_UPGRADE_COST; }
    int attackSpeed() override { return CONSTANTS::FACTORY_ATTACK_SPEED; }
    int damage() override { return CONSTANTS::FACTORY_DAMAGE; }

    int productionAmount() { return !upgraded ?
                             CONSTANTS::FACTORY_BASE_PRODUCTION : CONSTANTS::FACTORY_UPGRADE_PRODUCTION; }
    int productionSpeed()  { return !upgraded ?
                             CONSTANTS::FACTORY_BASE_PRODUCTION_SPEED : CONSTANTS::FACTORY_UPGRADE_PRODUCTION_SPEED; }


    void doActions() override {
        if(timeCounter % productionSpeed() == 0) {
            produce();
        }
    }
    void produce() { callback->produce(shared_from_this()); }
    int removeValue() override { return !upgraded ?
                                CONSTANTS::FACTORY_BASE_REMOVE_VALUE : CONSTANTS::FACTORY_UPGRADE_REMOVE_VALUE; }
    // void getStats() override;
};


#endif //WARP_FACTORY_H
