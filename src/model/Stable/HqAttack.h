#ifndef WARP_HQATTACK_H
#define WARP_HQATTACK_H

#include <memory>

#include "../Constants.h"
#include "Hq.h"

class HqAttack : public Hq {
public:
    HqAttack(
        Coordinate position, const std::shared_ptr<FieldEntityCallbackClass> &game_model_callback);

    int max_hp() override { return Constants::HQATTACK_BASE_MAX_HP; }

    int cost() override { return Constants::HQATTACK_BASE_COST; }

    int upgrade_cost() override { return Constants::HQATTACK_UPGRADE_COST; }

    int attack_speed() override { return 10; }

    void update() override;

    void die() override;

    void attack() override;

    int remove_value() override;

    void take_damage(int amount) override;
    // void getStats() override;
};

#endif  // WARP_HQATTACK_H
