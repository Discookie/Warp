#ifndef WARP_SPECIAL_H
#define WARP_SPECIAL_H

#include <memory>

#include "../Constants.h"
#include "Stable.h"

class Special : public Stable {
public:
    Special(
        Coordinate position, const std::shared_ptr<FieldEntityCallbackClass> &game_model_callback);

    int max_hp() override { return Constants::SPECIAL_BASE_MAX_HP; }

    int cost() override { return Constants::SPECIAL_BASE_COST; }

    int upgrade_cost() override { return Constants::SPECIAL_UPGRADE_COST; }

    int attack_speed() override { return 10; }

    void update() override;

    void die() override;

    void attack() override;

    std::vector<FieldEntity>&& collect_atteced_entities(
        const std::vector<std::vector<Field>>& fields) override;

    int get_damage() override;

    int remove_value() override { return 0; }

    void take_damage(int amount) override {}
    // void getStats() override;
};

#endif  // WARP_SPECIAL_H
