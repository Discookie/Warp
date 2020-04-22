#ifndef WARP_HQATTACK_H
#define WARP_HQATTACK_H

#include <memory>

#include "Hq.h"
#include "../Constants.h"

class HqAttack : public Hq {
public:
    HqAttack(Coordinate position,
             const std::shared_ptr<FieldEntityCallback> &game_model_callback) :
            Hq(position, game_model_callback) {
        this->hp = Constants::HQATTACK_MAX_HP;
    }

    int max_hp() override { return Constants::HQATTACK_MAX_HP; }

    int cost() override { return Constants::HQATTACK_BASE_COST; }

    int upgrade_cost() override { return Constants::HQATTACK_UPGRADE_COST; }

    int attack_speed() override { return Constants::HQATTACK_ATTACKSPEED; }

    int damage() override { return Constants::HQATTACK_DAMAGE; }

    void attack_entities(std::vector<std::vector<Field>> &fields) override {
        for (int i = this->position.x + 1; i < fields.size(); i++) {
            if (fields[i][this->position.y].get_team_status() == Team::TeamEnemy) {
                auto me = fields[i][this->position.y].get_moving_entities();
                for (auto &m : me) {
                    m->take_damage(this->damage());
                }
            }
        }
    }

    void do_actions() override {
        if (time_counter % attack_speed() == 0) {
            attack();
        }
    }

    int remove_value() override { return Constants::HQATTACK_REMOVE_VALUE; }
    // void getStats() override;

    EntityType get_entity_type() const override {
        return EntityType::TypeHqAttack;
    }
};


#endif //WARP_HQATTACK_H
