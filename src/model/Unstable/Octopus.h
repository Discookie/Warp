#ifndef WARP_OCTOPUS_H
#define WARP_OCTOPUS_H

#include "Enemy.h"

class Octopus : public Enemy {
public:
    Octopus(Coordinate position, const std::shared_ptr<FieldEntityCallbackClass>& gameModelCallback, int vectorPos) :
    Enemy(position, gameModelCallback, vectorPos){
        this->hp = CONSTANTS::OCTOPUS_MAX_HP;
    }
    int maxHp() override { return CONSTANTS::OCTOPUS_MAX_HP; }
    int moveSpeed() override { return CONSTANTS::OCTOPUS_MOVESPEED; }
    int attackSpeed() override { return  CONSTANTS::OCTOPUS_ATTACKSPEED; }
    int damage() override { return CONSTANTS::OCTOPUS_DAMAGE; }
};


#endif //WARP_OCTOPUS_H
