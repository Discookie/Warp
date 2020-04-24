#ifndef WARP_SNIPERTOWER_H
#define WARP_SNIPERTOWER_H

#include <memory>

#include "Stable.h"
#include "../Constants.h"

class SniperTower : public Stable {
private:
    // Actions
    void do_actions() override {
        if (time_counter % attack_speed() == 0) {
            attack();
        }
    }

public:
    SniperTower(Coordinate position,
                const std::shared_ptr<FieldEntityCallback> &game_model_callback) :
            Stable(position, game_model_callback) {
        this->upgraded = false;
        this->hp = Constants::SNIPERTOWER_MAX_HP;
    }

    int max_hp() const override { return Constants::SNIPERTOWER_MAX_HP; }

    int cost() const override { return Constants::SNIPERTOWER_BASE_COST(); }

    int upgrade_cost() const override { return Constants::SNIPERTOWER_UPGRADE_COST(); }

    int attack_speed() const override {
        return !upgraded ?
               Constants::SNIPERTOWER_BASE_ATTACKSPEED : Constants::SNIPERTOWER_UPGRADE_ATTACKSPEED;
    }

    int damage() const override {
        return !upgraded ?
               Constants::SNIPERTOWER_BASE_DAMAGE() : Constants::SNIPERTOWER_UPGRADE_DAMAGE();
    }

    void attack_entities(std::vector<std::vector<Field>> &fields) override {
        int nearest_distance = 10000;
        int current_distance;
        Coordinate target_position{-1, -1};
        for (auto &fv: fields) {
            for (auto &f:fv) {
                if (f.get_team_status() == Team::TeamEnemy) {
                    current_distance = distance(this->position, f.get_position());
                    if (current_distance < nearest_distance) {
                        nearest_distance = current_distance;
                        target_position = f.get_position();
                    }
                }
            }
        }
        if (0 <= target_position.x && target_position.x < 12 &&
            0 <= target_position.y && target_position.y < 10) {
            fields[target_position.x][target_position.y].get_moving_entities()[0]->take_damage(this->damage());
        }
    }

    int remove_value() const override {
        return !upgraded ?
               Constants::SNIPERTOWER_BASE_REMOVE_VALUE : Constants::SNIPERTOWER_UPGRADE_REMOVE_VALUE;
    }
    // void getStats() override;

    EntityType get_entity_type() const override {
        return EntityType::TypeSniperTower;
    }
};


#endif //WARP_SNIPERTOWER_H
