#ifndef WARP_HQDEFENSE_H
#define WARP_HQDEFENSE_H

#include <memory>

#include "Hq.h"
#include "../Constants.h"

class HqDefense : public Hq {
public:
    HqDefense(std::pair<int, int> position, const std::shared_ptr<FieldEntityCallbackClass>& gameModelCallback);

    int maxHp() override { return CONSTANTS::HQDEFENSE_BASE_MAX_HP; }
    int cost() override { return  CONSTANTS::HQDEFENSE_BASE_COST; }
    int upgradeCost() override { return CONSTANTS::HQDEFENSE_UPGRADE_COST; }
    int attackSpeed() override { return 10; }

    void update() override;
    void die() override;
    void attack() override {}
    int removeValue() override;
    void takeDamage(int amount) override;
    // void getStats() override;
};


#endif //WARP_HQDEFENSE_H
