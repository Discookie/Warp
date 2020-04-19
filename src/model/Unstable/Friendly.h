#ifndef WARP_FRIENDLY_H
#define WARP_FRIENDLY_H

#include "Unstable.h"
#include "../Constants.h"

class Friendly : public Unstable {
public:
    Friendly(Coordinate position, const std::shared_ptr<FieldEntityCallbackClass>& game_model_callback, int vector_pos) :
            Unstable(position, game_model_callback, vector_pos) {
        this->hp = Constants::FRIENDLY_MAX_HP;
    }

    bool is_friendly() final { return true; }

    int max_hp() override { return Constants::FRIENDLY_MAX_HP; }

    int move_speed() override { return Constants::FRIENDLY_MOVESPEED; }

    int cost() override { return Constants::FRIENDLY_COST; }

    int attack_speed() override { return Constants::FRIENDLY_ATTACKSPEED; }

    int damage() override { return Constants::FRIENDLY_DAMAGE; }

    std::optional<Coordinate> move_to(const std::vector<std::vector<Field>> &) override {}

    void attack_entities(const std::vector<std::vector<Field>> &) override {}
};


#endif //WARP_FRIENDLY_H
