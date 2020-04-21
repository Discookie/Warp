#ifndef WARP_SPECIAL_H
#define WARP_SPECIAL_H

#include <memory>

#include "Stable.h"
#include "../Constants.h"

class Special : public Stable{
public:
    Special(Coordinate position,
            const std::shared_ptr<FieldEntityCallback> &game_model_callback) :
            Stable(position, game_model_callback) {
        this->upgraded = true;
        this->hp = Constants::SPECIAL_MAX_HP;
    }

    int max_hp() override { return Constants::SPECIAL_MAX_HP; }

    int cost() override { return Constants::SPECIAL_BASE_COST; }

    int upgrade_cost() override { return Constants::SPECIAL_UPGRADE_COST; }

    int attack_speed() override { return Constants::SPECIAL_ATTACKSPEED; }

    int damage() override { return Constants::SPECIAL_DAMAGE; }

    void attack_entities(std::vector<std::vector<Field>> &fields) override {
        for (auto &vf:fields) {
            for (auto &f:vf) {
                if (abs(f.get_position().x - this->get_position().x) <= Constants::TESLACOIL_ATTACK_RANGE &&
                    abs(f.get_position().y - this->get_position().y) <= Constants::TESLACOIL_ATTACK_RANGE) {
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
            die();
        }
    }

    int remove_value() override { return Constants::SPECIAL_REMOVE_VALUE; }

    void take_damage(int amount) override {}
    // void getStats() override;

    EntityType get_entity_type() const override {
        return EntityType::TypeSpecial;
    }
};


#endif //WARP_SPECIAL_H
