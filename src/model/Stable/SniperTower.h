#ifndef WARP_SNIPERTOWER_H
#define WARP_SNIPERTOWER_H

#include <memory>

#include "Stable.h"
#include "../Constants.h"

class SniperTower : public Stable{
public:
    SniperTower(std::pair<int, int> position, const std::shared_ptr<FieldEntityCallbackClass>& gameModelCallback);

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
