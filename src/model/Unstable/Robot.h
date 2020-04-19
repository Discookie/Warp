#ifndef WARP_ROBOT_H
#define WARP_ROBOT_H

#include "Enemy.h"

class Robot : public Enemy{
public:
    Robot(Coordinate position, const std::shared_ptr<FieldEntityCallbackClass>& gameModelCallback, int vectorPos) :
        Enemy(position, gameModelCallback, vectorPos) {
        this->hp = CONSTANTS::ROBOT_MAX_HP;
    }
    int maxHp() override { return CONSTANTS::ROBOT_MAX_HP; }
    int moveSpeed() override { return CONSTANTS::ROBOT_MOVESPEED; }
    int attackSpeed() override { return  CONSTANTS::ROBOT_ATTACKSPEED; }
    int damage() override { return CONSTANTS::ROBOT_DAMAGE; }
};

#endif //WARP_ROBOT_H
