#ifndef WARP_ENEMY_H
#define WARP_ENEMY_H

#include "Unstable.h"
#include "../Constants.h"

class Enemy : public Unstable{
public:
    Enemy(Coordinate position, const std::shared_ptr<FieldEntityCallbackClass>& gameModelCallback, int vectorPos) :
        Unstable(position, gameModelCallback, vectorPos){}
    int cost() final { return CONSTANTS::ENEMY_COST; }
    bool isFriendly() final { return false; }
};


#endif //WARP_ENEMY_H
