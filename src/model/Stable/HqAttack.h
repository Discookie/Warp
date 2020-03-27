#ifndef WARP_HQATTACK_H
#define WARP_HQATTACK_H

#include <memory>

#include "Hq.h"
#include "../Constants.h"

class HqAttack : public Hq {
public:
    HqAttack(std::pair<int, int> position, const std::shared_ptr<FieldEntityCallbackClass>& gameModelCallback);

    int maxHp() override { return CONSTANTS::HQATTACK_BASE_MAX_HP; }
    int cost() override { return CONSTANTS::HQATTACK_BASE_COST; }
    int upgradeCost() override { return CONSTANTS::HQATTACK_UPGRADE_COST; }
    int attackSpeed() override { return 10; }

    void update() override;
    void die() override;
    void attack() override;
    int removeValue() override;
    void takeDamage(int amount) override;
    // void getStats() override;
};


#endif //WARP_HQATTACK_H
