#ifndef WARP_FACTORY_H
#define WARP_FACTORY_H

#include <memory>

#include "../Constants.h"
#include "Stable.h"

class Factory : public Stable {
public:
    Factory(
        Coordinate position, const std::shared_ptr<FieldEntityCallbackClass> &game_model_callback);

    int max_hp() override {
        return !upgraded ? Constants::FACTORY_BASE_MAX_HP : Constants::FACTORY_UPGRADE_MAX_HP;
    }

    int cost() override { return Constants::FACTORY_BASE_COST; }

    int upgrade_cost() override { return Constants::FACTORY_UPGRADE_COST; }

    int attack_speed() override { return Constants::FACTORY_ATTACK_SPEED; }

    int production_amount() {
        return !upgraded ? Constants::FACTORY_BASE_PRODUCTION
                         : Constants::FACTORY_UPGRADE_PRODUCTION;
    }

    int production_speed() {
        return !upgraded ? Constants::FACTORY_BASE_PRODUCTION_SPEED
                         : Constants::FACTORY_UPGRADE_PRODUCTION_SPEED;
    }

    void produce();

    void update() override;

    void die() override;

    void attack() override {}

    int remove_value() override {
        return !upgraded ? Constants::FACTORY_BASE_REMOVE_VALUE
                         : Constants::FACTORY_UPGRADE_REMOVE_VALUE;
    }

    void take_damage(int amount) override;
    // void getStats() override;
};

#endif  // WARP_FACTORY_H
