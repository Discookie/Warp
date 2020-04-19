#ifndef WARP_ALIEN_H
#define WARP_ALIEN_H

#include "Enemy.h"

class Alien : public Enemy {
public:
    Alien(Coordinate position, const std::shared_ptr<FieldEntityCallbackClass> &game_model_callback, int vector_pos) :
            Enemy(position, game_model_callback, vector_pos) {
        this->hp = Constants::ALIEN_MAX_HP;
    }

    int max_hp() override { return Constants::ALIEN_MAX_HP; }

    int move_speed() override { return Constants::ALIEN_MOVESPEED; }

    int attack_speed() override { return Constants::ALIEN_ATTACKSPEED; }

    int damage() override { return Constants::ALIEN_DAMAGE; }

    std::optional<Coordinate> move_to(const std::vector<std::vector<Field>> &) override {}

    void attack_entities(const std::vector<std::vector<Field>> &) override {}
};


#endif //WARP_ALIEN_H
