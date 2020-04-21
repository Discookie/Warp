#ifndef WARP_ENEMY_H
#define WARP_ENEMY_H

#include "Unstable.h"
#include "../Constants.h"

class Enemy : public Unstable{
public:
    Enemy(Coordinate position, const std::shared_ptr<FieldEntityCallback> &game_model_callback, int vector_pos) :
            Unstable(position, game_model_callback, vector_pos){}
    explicit Enemy(const std::shared_ptr<FieldEntityCallback> &game_model_callback)
        : Unstable(game_model_callback) {}
    int cost() final { return Constants::ENEMY_COST; }
    bool is_friendly() final { return false; }
};


#endif //WARP_ENEMY_H
