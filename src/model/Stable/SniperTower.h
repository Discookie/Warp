#ifndef WARP_SNIPERTOWER_H
#define WARP_SNIPERTOWER_H

#include "Stable.h"
#include "../Constants.h"

class SniperTower : public Stable{
public:
    explicit SniperTower(std::pair<int, int> position, CallbackClass gameModelCallback);
    int maxHp() override { return CONSTANTS::SNIPERTOWER_BASE_MAX_HP; }
    int cost() override { return CONSTANTS::SNIPERTOWER_BASE_COST; }
    int upgradeCost() override { return CONSTANTS::SNIPERTOWER_UPGRADE_COST; }
    int attackSpeed() override { return 10; }

    void update() override;
    void die() override;
    void attack() override;
    int removeValue() override;
    void takeDamage(int amount) override;
    // void getStats() override;
};


#endif //WARP_SNIPERTOWER_H
