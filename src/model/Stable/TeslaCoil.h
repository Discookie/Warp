#ifndef WARP_TESLACOIL_H
#define WARP_TESLACOIL_H

#include <memory>

#include "Stable.h"
#include "../Constants.h"

class TeslaCoil : public Stable{
public:
    TeslaCoil(Coordinate position,
              const std::shared_ptr<FieldEntityCallback> &game_model_callback) :
            Stable(position, game_model_callback){
        this->upgraded = false;
        this->hp = Constants::TESLACOIL_MAX_HP;
    }

    int max_hp() override { return Constants::TESLACOIL_MAX_HP; }

    int cost() override { return Constants::TESLACOIL_BASE_COST; }

    int upgrade_cost() override { return Constants::TESLACOIL_UPGRADE_COST; }

    int attack_speed() override {
        return !upgraded ?
               Constants::TESLACOIL_BASE_ATTACKSPEED : Constants::TESLACOIL_UPGRADE_ATTACKSPEED;
    }

    int damage() override {
        return !upgraded ?
               Constants::TESLACOIL_BASE_DAMAGE : Constants::TESLACOIL_UPGRADE_DAMAGE;
    }

    void attack_entities(std::vector<std::vector<Field>> &fields) override {
        for (auto &vf:fields) {
            for (auto &f:vf) {
                if (abs(f.get_position().x - this->get_position().x) <= Constants::SPECIAL_ATTACK_RANGE &&
                    abs(f.get_position().y - this->get_position().y) <= Constants::SPECIAL_ATTACK_RANGE) {
                    if (f.get_team_status() == Team::Enemy) {
                        auto me = f.get_moving_entities();
                        for (auto &m : me) {
                            m->take_damage(this->damage());
                        }
                    }
                }
            }
        }
    }

    void do_actions() override {
        if (time_counter % attack_speed() == 0) {
            attack();
        }
    }

    int remove_value() override {
        return !upgraded ?
               Constants::TESLACOIL_BASE_REMOVE_VALUE : Constants::TESLACOIL_UPGRADE_REMOVE_VALUE;
    }
    // void getStats() override;

    EntityType get_entity_type() const override {
        return EntityType::TypeTeslaCoil;
    }
};


#endif //WARP_TESLACOIL_H
