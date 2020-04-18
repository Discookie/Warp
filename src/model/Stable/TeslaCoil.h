#ifndef WARP_TESLACOIL_H
#define WARP_TESLACOIL_H

#include <memory>

#include "../Constants.h"
#include "Stable.h"

class TeslaCoil : public Stable {
public:
    TeslaCoil(
        Coordinate position, const std::shared_ptr<FieldEntityCallbackClass> &game_model_callback);

    int max_hp() override { return Constants::TESLACOIL_BASE_MAX_HP; }

    int cost() override { return Constants::TESLACOIL_BASE_COST; }

    int upgrade_cost() override { return Constants::TESLACOIL_UPGRADE_COST; }

    int attack_speed() override { return 10; }

    void update() override;

    void die() override;

    void attack() override;

    std::vector<FieldEntity>&& collect_atteced_entities(
        const std::vector<std::vector<Field>>& fields) override;

    int get_damage() override;

    int remove_value() override;

    void take_damage(int amount) override;
    // void getStats() override;
};

#endif  // WARP_TESLACOIL_H
