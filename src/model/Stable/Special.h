#ifndef WARP_SPECIAL_H
#define WARP_SPECIAL_H

#include <memory>

#include "Stable.h"
#include "../Constants.h"

class Special : public Stable{
public:
    Special(std::pair<int, int> position, const std::shared_ptr<FieldEntityCallbackClass>& gameModelCallback);

    int maxHp() override { return CONSTANTS::SPECIAL_BASE_MAX_HP; }
    int cost() override { return CONSTANTS::SPECIAL_BASE_COST; }
    int upgradeCost() override { return CONSTANTS::SPECIAL_UPGRADE_COST; }
    int attackSpeed() override { return 10; }

    void update() override;
    void die() override;
    void attack() override;
    int removeValue() override { return 0; }
    void takeDamage(int amount) override {}
    // void getStats() override;
};


#endif //WARP_SPECIAL_H
