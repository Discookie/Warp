#ifndef WARP_OCTOPUS_H
#define WARP_OCTOPUS_H

#include "Enemy.h"

class Octopus : public Enemy {
public:
    Octopus(Coordinate position, const std::shared_ptr<FieldEntityCallback> &game_model_callback, int vector_pos) :
            Enemy(position, game_model_callback, vector_pos) {
        this->hp = Constants::OCTOPUS_MAX_HP;
    }

    int max_hp() override { return Constants::OCTOPUS_MAX_HP; }

    int move_speed() override { return Constants::OCTOPUS_MOVESPEED; }

    int attack_speed() override { return Constants::OCTOPUS_ATTACKSPEED; }

    int damage() override { return Constants::OCTOPUS_DAMAGE; }

    std::optional<Coordinate> move_to(const std::vector<std::vector<Field>> &fields) override {
        if (this->position.x-- >= 0) {
            if (fields[this->position.x--][this->position.y].get_team_status() != Team::Friendly) {
                return std::optional<Coordinate>({this->position.x--, this->position.y});
            }
        } else if (this->position.x-- < 0) {
            throw std::logic_error("very bad, game already over");
        }
        return std::nullopt;
    }

    void attack_entities(std::vector<std::vector<Field>> &) override {

    }
};


#endif //WARP_OCTOPUS_H
