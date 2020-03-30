#ifndef WARP_HQDEFENSE_H
#define WARP_HQDEFENSE_H

#include <memory>

#include "../Constants.h"
#include "Hq.h"

class HqDefense : public Hq {
public:
    HqDefense(
        Coordinate position, const std::shared_ptr<FieldEntityCallbackClass> &game_model_callback);

    int max_hp() override { return Constants::HQDEFENSE_BASE_MAX_HP; }

    int cost() override { return Constants::HQDEFENSE_BASE_COST; }

    int upgrade_cost() override { return Constants::HQDEFENSE_UPGRADE_COST; }

    int attack_speed() override { return 10; }

    void update() override;

    void die() override;

    void attack() override {}

    int remove_value() override;

    void take_damage(int amount) override;
    // void getStats() override;
};

#endif  // WARP_HQDEFENSE_H
