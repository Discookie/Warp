#ifndef WARP_FRIENDLY_H
#define WARP_FRIENDLY_H

#include "Unstable.h"
#include "../Constants.h"

class Friendly : public Unstable {
public:
    Friendly(Coordinate position, const std::shared_ptr<FieldEntityCallback> &game_model_callback, int vector_pos) :
            Unstable(position, game_model_callback, vector_pos) {
        this->hp = Constants::FRIENDLY_MAX_HP;
    }

    bool is_friendly() final { return true; }

    int max_hp() override { return Constants::FRIENDLY_MAX_HP; }

    int move_speed() override { return Constants::FRIENDLY_MOVESPEED; }

    int cost() override { return Constants::FRIENDLY_COST; }

    int attack_speed() override { return Constants::FRIENDLY_ATTACKSPEED; }

    int damage() override { return Constants::FRIENDLY_DAMAGE; }

    std::optional<Coordinate> move_to(const std::vector<std::vector<Field>> &fields) override {
        if (this->position.x + 1 < fields.size()) {
            if (fields[this->position.x + 1][this->position.y].get_team_status() != Team::TeamEnemy) {
                return std::optional<Coordinate>({this->position.x + 1, this->position.y});
            }
        } else if (this->position.x + 1 == fields.size()) {
            return std::optional<Coordinate>({-1, -1});
        }
        return std::nullopt;
    }

    void attack_entities(std::vector<std::vector<Field>> &fields) override {
        if (this->position.x + 1 < fields.size()) {
            if (fields[this->position.x + 1][this->position.y].get_team_status() == Team::TeamEnemy) {
                auto me = fields[this->position.x + 1][this->position.y].get_moving_entities();
                if (!me.empty()) {
                    me[0]->take_damage(this->damage());
                }
            }
        }
    }
    EntityType get_entity_type() const override {
        return EntityType::TypeFriendly;
    }
};


#endif //WARP_FRIENDLY_H
