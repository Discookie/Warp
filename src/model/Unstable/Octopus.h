#ifndef WARP_OCTOPUS_H
#define WARP_OCTOPUS_H

#include "Enemy.h"

class Octopus : public Enemy {
public:
    Octopus(Coordinate position, const std::shared_ptr<FieldEntityCallbackClass>& game_model_callback, int vector_pos) :
    Enemy(position, game_model_callback, vector_pos){
        this->hp = Constants::OCTOPUS_MAX_HP;
    }
    int max_hp() override { return Constants::OCTOPUS_MAX_HP; }
    int move_speed() override { return Constants::OCTOPUS_MOVESPEED; }
    int attack_speed() override { return  Constants::OCTOPUS_ATTACKSPEED; }
    int damage() override { return Constants::OCTOPUS_DAMAGE; }
};


#endif //WARP_OCTOPUS_H
