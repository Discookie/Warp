#ifndef WARP_LASERTOWER_H
#define WARP_LASERTOWER_H

#include <memory>

#include "../Constants.h"
#include "Stable.h"

class LaserTower : public Stable {
public:
    LaserTower(
        Coordinate position, const std::shared_ptr<FieldEntityCallbackClass>& game_model_callback);

    int max_hp() override { return Constants::LASERTOWER_BASE_MAX_HP; }

    int cost() override { return Constants::LASERTOWER_BASE_COST; }

    int upgrade_cost() override { return Constants::LASERTOWER_UPGRADE_COST; }

    int attack_speed() override { return 10; }

    std::vector<FieldEntity>&& collect_atteced_entities(
        const std::vector<std::vector<Field>>& fields) override;

    int get_damage() override;

    void update() override;

    void die() override;

    void attack() override;

    int remove_value() override;

    void take_damage(int amount) override;
    // void getStats() override;
};

#endif  // WARP_LASERTOWER_H
