#ifndef WARP_TESLACOIL_H
#define WARP_TESLACOIL_H

#include "Stable.h"
#include "../Constants.h"

class TeslaCoil : public Stable{
public:
    explicit TeslaCoil(std::pair<int, int> position, CallbackClass gameModelCallback);
    int maxHp() override { return CONSTANTS::TESLACOIL_BASE_MAX_HP; }
    int cost() override { return CONSTANTS::TESLACOIL_BASE_COST; }
    int upgradeCost() override { return CONSTANTS::TESLACOIL_UPGRADE_COST; }
    int attackSpeed() override { return 10; }

    void update() override;
    void die() override;
    void attack() override;
    int removeValue() override;
    void takeDamage(int amount) override;
    // void getStats() override;
};


#endif //WARP_TESLACOIL_H
