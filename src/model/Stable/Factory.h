#ifndef WARP_FACTORY_H
#define WARP_FACTORY_H

#include <memory>

#include "Stable.h"
#include "../Constants.h"

class Factory : public Stable {
public:
    Factory(std::pair<int, int> position, const std::shared_ptr<CallbackClass>& callback);
    explicit Factory(Factory *pFactory);

    int maxHp() override { return !isUpgraded ?
                          CONSTANTS::FACTORY_BASE_MAX_HP : CONSTANTS::FACTORY_UPGRADE_MAX_HP; }
    int cost() override { return CONSTANTS::FACTORY_BASE_COST; }
    int upgradeCost() override { return CONSTANTS::FACTORY_UPGRADE_COST; }
    int attackSpeed() override { return CONSTANTS::FACTORY_ATTACK_SPEED; }

    int productionAmount() { return !isUpgraded ?
                            CONSTANTS::FACTORY_BASE_PRODUCTION : CONSTANTS::FACTORY_UPGRADE_PRODUCTION; }
    int productionSpeed()  { return !isUpgraded ?
                            CONSTANTS::FACTORY_BASE_PRODUCTION_SPEED : CONSTANTS::FACTORY_UPGRADE_PRODUCTION_SPEED; }

    void produce();
    void update() override;
    void die() override;
    void attack() override {}
    int removeValue() override { return !isUpgraded ?
                                CONSTANTS::FACTORY_BASE_REMOVE_VALUE : CONSTANTS::FACTORY_UPGRADE_REMOVE_VALUE; }
    void takeDamage(int amount) override;
    // void getStats() override;
};


#endif //WARP_FACTORY_H
