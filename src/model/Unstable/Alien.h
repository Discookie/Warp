#ifndef WARP_ALIEN_H
#define WARP_ALIEN_H

#include "Enemy.h"

class Alien : public Enemy{
public:
    Alien(Coordinate position, const std::shared_ptr<FieldEntityCallbackClass>& gameModelCallback, int vectorPos) :
        Enemy(position, gameModelCallback, vectorPos){
        this->hp = CONSTANTS::ALIEN_MAX_HP;
    }
    int maxHp() override { return CONSTANTS::ALIEN_MAX_HP; }
    int moveSpeed() override { return CONSTANTS::ALIEN_MOVESPEED; }
    int attackSpeed() override { return  CONSTANTS::ALIEN_ATTACKSPEED; }
    int damage() override { return CONSTANTS::ALIEN_DAMAGE; }
};


#endif //WARP_ALIEN_H
