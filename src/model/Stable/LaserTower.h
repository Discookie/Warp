#ifndef WARP_LASERTOWER_H
#define WARP_LASERTOWER_H

#include <memory>

#include "Stable.h"
#include "../Constants.h"

class LaserTower : public Stable{
public:
    LaserTower(std::pair<int, int> position, const std::shared_ptr<CallbackClass>& gameModelCallback);
    explicit LaserTower(LaserTower *pLaserTower);

    int maxHp() override { return CONSTANTS::LASERTOWER_BASE_MAX_HP; }
    int cost() override { return CONSTANTS::LASERTOWER_BASE_COST; }
    int upgradeCost() override { return CONSTANTS::LASERTOWER_UPGRADE_COST; }
    int attackSpeed() override { return 10; }

    void update() override;
    void die() override;
    void attack() override;
    int removeValue() override;
    void takeDamage(int amount) override;
    // void getStats() override;
};


#endif //WARP_LASERTOWER_H
