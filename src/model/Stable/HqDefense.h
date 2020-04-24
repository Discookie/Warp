#ifndef WARP_HQDEFENSE_H
#define WARP_HQDEFENSE_H

#include <memory>

#include "Hq.h"
#include "../Constants.h"

class HqDefense : public Hq {
private:
    // Actions
    void attack_entities(std::vector<std::vector<Field>> &) override {}

    void do_actions() override {}

public:
    HqDefense(Coordinate position,
              const std::shared_ptr<FieldEntityCallback> &game_model_callback) :
            Hq(position, game_model_callback) {
        this->hp = Constants::HQDEFENSE_MAX_HP;
    }

    int max_hp() const override { return Constants::HQDEFENSE_MAX_HP; }

    int cost() const override { return Constants::HQDEFENSE_BASE_COST(); }

    int upgrade_cost() const override { return Constants::HQDEFENSE_UPGRADE_COST; }

    int attack_speed() const override { return Constants::HQDEFENSE_ATTACKSPEED; }

    int damage() const override { return Constants::HQDEFENSE_DAMAGE; }

    int remove_value() const override { return Constants::HQDEFENSE_REMOVE_VALUE; }
    // void getStats() override;

    EntityType get_entity_type() const override {
        return EntityType::TypeHqDefense;
    }
};


#endif //WARP_HQDEFENSE_H
