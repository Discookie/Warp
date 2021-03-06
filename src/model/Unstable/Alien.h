#ifndef WARP_ALIEN_H
#define WARP_ALIEN_H

#include "Enemy.h"

class Alien : public Enemy {
public:
    Alien(Coordinate position, const std::shared_ptr<FieldEntityCallback> &game_model_callback, int vector_pos) :
            Enemy(position, game_model_callback, vector_pos) {
        this->hp = Constants::ALIEN_MAX_HP();
    }

    int max_hp() const override { return Constants::ALIEN_MAX_HP(); }

    int move_speed() const override { return Constants::ALIEN_MOVESPEED(); }

    int attack_speed() const override { return Constants::ALIEN_ATTACKSPEED; }

    int damage() const override { return Constants::ALIEN_DAMAGE; }

    std::optional<Coordinate> move_to(const std::vector<std::vector<Field>> &fields) override {
        if (this->position.x - 1 >= 0) {
            if (fields[this->position.x - 1][this->position.y].get_team_status() != Team::TeamFriendly) {
                return std::optional<Coordinate>({this->position.x - 1, this->position.y});
            }
        } else if (this->position.x - 1 < 0) {
            throw std::logic_error("very bad, game already over");
        }
        return std::nullopt;
    }

    void attack_entities(std::vector<std::vector<Field>> &fields) override {
        if (this->position.x - 1 >= 0) {
            if (fields[this->position.x - 1][this->position.y].get_team_status() == Team::TeamFriendly) {
                if (fields[this->position.x - 1][this->position.y].get_tower()) {
                    fields[this->position.x - 1][this->position.y].get_tower()->take_damage(this->damage());
                    return;
                } else {
                    auto me = fields[this->position.x - 1][this->position.y].get_moving_entities();
                    if (!me.empty()) {
                        me[0]->take_damage(this->damage());
                        return;
                    }
                }
            }
        }
    }

    EntityType get_entity_type() const override {
        return EntityType::TypeAlien;
    }
};


#endif //WARP_ALIEN_H
