#ifndef WARP_LASERTOWER_H
#define WARP_LASERTOWER_H

#include <memory>

#include "Stable.h"
#include "../Constants.h"

#include "../Field.h"

class LaserTower : public Stable {
public:
    LaserTower(Coordinate position, const std::shared_ptr<FieldEntityCallback> &game_model_callback)
            : Stable(position, game_model_callback) {
        this->upgraded = false;
        this->hp = Constants::LASERTOWER_MAX_HP;
    }

    int max_hp() override { return Constants::LASERTOWER_MAX_HP; }

    int cost() override { return Constants::LASERTOWER_BASE_COST; }

    int upgrade_cost() override { return Constants::LASERTOWER_UPGRADE_COST; }

    int attack_speed() override {
        return !upgraded ?
               Constants::LASERTOWER_BASE_ATTACKSPEED : Constants::LASERTOWER_UPGRADE_ATTACKSPEED;
    }

    int damage() override {
        return !upgraded ?
               Constants::LASERTOWER_BASE_DAMAGE : Constants::LASERTOWER_UPGRADE_DAMAGE;
    }

    void attack_entities(std::vector<std::vector<Field>> &fields) override {
        for (int i = this->position.x++; i < fields.size(); i++) {
            if (fields[i][this->position.y].get_team_status() == Team::Enemy) {
                auto me = fields[i][this->position.y].get_moving_entities();
                if (!me.empty()) {
                    me[0]->take_damage(this->damage());
                    return;
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
               Constants::LASERTOWER_BASE_REMOVE_VALUE : Constants::LASERTOWER_UPGRADE_REMOVE_VALUE;
    }
    // void getStats() override;

    EntityType get_entity_type() const override {
        return EntityType::TypeLaserTower;
    }
};


#endif //WARP_LASERTOWER_H
