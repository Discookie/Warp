#ifndef WARP_TESLACOIL_H
#define WARP_TESLACOIL_H

#include <memory>

#include "Stable.h"
#include "../Constants.h"

class TeslaCoil : public Stable {
private:
    // Actions
    void do_actions() override {
        if (time_counter % attack_speed() == 0) {
            attack();
        }
    }

public:
    TeslaCoil(Coordinate position,
              const std::shared_ptr<FieldEntityCallback> &game_model_callback) :
            Stable(position, game_model_callback) {
        this->upgraded = false;
        this->hp = Constants::TESLACOIL_MAX_HP;
    }

    int max_hp() const override { return Constants::TESLACOIL_MAX_HP; }

    int cost() const override { return Constants::TESLACOIL_BASE_COST(); }

    int upgrade_cost() const override { return Constants::TESLACOIL_UPGRADE_COST(); }

    int attack_speed() const override {
        return !upgraded ?
               Constants::TESLACOIL_BASE_ATTACKSPEED : Constants::TESLACOIL_UPGRADE_ATTACKSPEED;
    }

    int damage() const override {
        return !upgraded ?
               Constants::TESLACOIL_BASE_DAMAGE() : Constants::TESLACOIL_UPGRADE_DAMAGE();
    }

    void attack_entities(std::vector<std::vector<Field>> &fields) override {
        for (auto &vf:fields) {
            for (auto &f:vf) {
                if (distance(this->get_position(), f.get_position()) <= Constants::TESLACOIL_ATTACK_RANGE) {
                    if (f.get_team_status() == Team::TeamEnemy) {
                        for (int i = 0; i < f.get_moving_entities().size(); ++i) {
                            int s = f.get_moving_entities().size();
                            f.get_moving_entities()[i]->take_damage(this->damage());
                            if (s != f.get_moving_entities().size()) {
                                --i;
                            }
                        }
                    }
                }
            }
        }
    }


    int remove_value() const override {
        return !upgraded ?
               Constants::TESLACOIL_BASE_REMOVE_VALUE : Constants::TESLACOIL_UPGRADE_REMOVE_VALUE;
    }
    // void getStats() override;

    EntityType get_entity_type() const override {
        return EntityType::TypeTeslaCoil;
    }
};


#endif //WARP_TESLACOIL_H
