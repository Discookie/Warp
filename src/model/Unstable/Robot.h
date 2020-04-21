#ifndef WARP_ROBOT_H
#define WARP_ROBOT_H

#include "Enemy.h"

class Robot : public Enemy {
public:
    Robot(Coordinate position, const std::shared_ptr<FieldEntityCallback> &game_model_callback, int vector_pos) :
            Enemy(position, game_model_callback, vector_pos) {
        this->hp = Constants::ROBOT_MAX_HP;
    }

    int max_hp() override { return Constants::ROBOT_MAX_HP; }

    int move_speed() override { return Constants::ROBOT_MOVESPEED; }

    int attack_speed() override { return Constants::ROBOT_ATTACKSPEED; }

    int damage() override { return Constants::ROBOT_DAMAGE; }

    std::optional<Coordinate> move_to(const std::vector<std::vector<Field>> &fields) override {
        // NOT FINAL
        if (this->position.x-- >= 0) {
            if (fields[this->position.x--][this->position.y].get_team_status() != Team::Friendly) {
                return std::optional<Coordinate>({this->position.x--, this->position.y});
            }
        } else if (this->position.x-- < 0) {
            throw std::logic_error("very bad, game already over");
        }
        return std::nullopt;
    }

    void attack_entities(std::vector<std::vector<Field>> &fields) override {
        for (int i = this->position.x--; i >= 0; i--) {
            if (fields[i][this->position.y].get_team_status() == Team::Friendly) {
                if (fields[i][this->position.y].get_tower()) {
                    fields[i][this->position.y].get_tower()->take_damage(this->damage());
                    return;
                } else {
                    auto me = fields[i][this->position.y].get_moving_entities();
                    if (!me.empty()) {
                        me[0]->take_damage(this->damage());
                        return;
                    }
                }
            }
        }
    }
};

#endif //WARP_ROBOT_H
