#ifndef WARP_ROBOT_H
#define WARP_ROBOT_H

#include "Enemy.h"

class Robot : public Enemy{
public:
    Robot(Coordinate position, const std::shared_ptr<FieldEntityCallbackClass>& game_model_callback, int vector_pos) :
        Enemy(position, game_model_callback, vector_pos) {
        this->hp = Constants::ROBOT_MAX_HP;
    }
    int max_hp() override { return Constants::ROBOT_MAX_HP; }
    int move_speed() override { return Constants::ROBOT_MOVESPEED; }
    int attack_speed() override { return  Constants::ROBOT_ATTACKSPEED; }
    int damage() override { return Constants::ROBOT_DAMAGE; }
};

#endif //WARP_ROBOT_H
