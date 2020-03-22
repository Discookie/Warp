#ifndef WARP_FACTORY_H
#define WARP_FACTORY_H

#include "Stable.h"
#include "../Constants.h"

class Factory : public Stable {
public:
    Factory(std::pair<int, int> position, CallbackClass callback);
    int maxHp() override { return CONSTANTS::FACTORY_BASE_MAX_HP; }
    int cost() override { return CONSTANTS::FACTORY_BASE_COST; }
    int upgradeCost() override { return CONSTANTS::FACTORY_UPGRADE_COST; }
    int attackSpeed() override { return 10; }
    int production() { return CONSTANTS::FACTORY_BASE_PRODUCTION; }

    void update() override;
    void die() override;
    void attack() override;
    int removeValue() override;
    void takeDamage(int amount) override;
    // void getStats() override;
};


#endif //WARP_FACTORY_H
