#ifndef WARP_ROBOT_H
#define WARP_ROBOT_H

#include "Enemy.h"

class Robot : public Enemy {
public:
    Robot(Coordinate position, const std::shared_ptr<FieldEntityCallback> &game_model_callback, int vector_pos) :
            Enemy(position, game_model_callback, vector_pos) {
        this->hp = Constants::ROBOT_MAX_HP;
    }

    int max_hp() const override { return Constants::ROBOT_MAX_HP; }

    int move_speed() const override { return Constants::ROBOT_MOVESPEED; }

    int attack_speed() const override { return Constants::ROBOT_ATTACKSPEED; }

    int damage() const override { return Constants::ROBOT_DAMAGE; }

    std::optional<Coordinate> move_to(const std::vector<std::vector<Field>> &fields) override {
        if (this->position.x - 1 < 0) { throw std::logic_error("very bad, game already over"); }
        bool in_row_av = fields[this->position.x - 1][this->position.y].get_team_status() != Team::TeamFriendly;
        bool above_av = false;
        bool below_av = false;
        if (this->position.y + 1 < 12) {
            above_av = fields[this->position.x - 1][this->position.y + 1].get_team_status() != Team::TeamFriendly;
        }
        if (this->position.y - 1 >= 0) {
            below_av = fields[this->position.x - 1][this->position.y - 1].get_team_status() != Team::TeamFriendly;
        }
        int in_row = 10000;
        int above = 10000;
        int below = 10000;
        if (in_row_av) {
            for (int i = this->position.x - 1; i >= 0; i--) {
                if (fields[i][position.y].get_team_status() == Team::TeamFriendly) {
                    in_row++;
                }
            }
        }
        if (above_av) {
            above = 0;
            for (int i = this->position.x - 1; i >= 0; i--) {
                if (fields[i][position.y + 1].get_team_status() == Team::TeamFriendly) {
                    above++;
                }
            }
        }
        if (below_av) {
            below = 0;
            for (int i = this->position.x - 1; i >= 0; i--) {
                if (fields[i][position.y - 1].get_team_status() == Team::TeamFriendly) {
                    below++;
                }
            }
        }
        if (in_row_av) {
            if (in_row <= above && in_row <= below) {
                return std::optional<Coordinate>({this->position.x - 1, this->position.y});
            }
        }
        if (above_av) {
            if (above < in_row && above < below) {
                return std::optional<Coordinate>({this->position.x - 1, this->position.y + 1});
            }
        }
        if (below_av) {
            if (below < in_row && below <= above) {
                return std::optional<Coordinate>({this->position.x - 1, this->position.y - 1});
            }
        }
        return std::nullopt;
    }

    void attack_entities(std::vector<std::vector<Field>> &fields) override {
        for (int i = this->position.x - 1; i >= 0; i--) {
            if (fields[i][this->position.y].get_team_status() == Team::TeamFriendly) {
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

    EntityType get_entity_type() const override {
        return EntityType::TypeRobot;
    }
};

#endif //WARP_ROBOT_H
