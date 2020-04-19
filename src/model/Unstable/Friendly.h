#ifndef WARP_FRIENDLY_H
#define WARP_FRIENDLY_H

#include "Unstable.h"
#include "../Constants.h"

class Friendly : public Unstable {
public:
    Friendly(Coordinate position, const std::shared_ptr<FieldEntityCallbackClass>& gameModelCallback, int vectorPos) :
        Unstable(position, gameModelCallback, vectorPos){
        this->hp = CONSTANTS::FRIENDLY_MAX_HP;
    }
    bool isFriendly() final { return true; }

    int maxHp() override { return CONSTANTS::FRIENDLY_MAX_HP; }
    int moveSpeed() override { return CONSTANTS::FRIENDLY_MOVESPEED; }
    int cost() override { return CONSTANTS::FRIENDLY_COST; }
    int attackSpeed() override { return  CONSTANTS::FRIENDLY_ATTACKSPEED; }
    int damage() override { return CONSTANTS::FRIENDLY_DAMAGE; }
};


#endif //WARP_FRIENDLY_H
