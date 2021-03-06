#ifndef WARP_ENEMY_H
#define WARP_ENEMY_H

#include "Unstable.h"
#include "../Constants.h"

class Enemy : public Unstable {
public:
    Enemy(Coordinate position, const std::shared_ptr<FieldEntityCallback> &game_model_callback, int vector_pos) :
            Unstable(position, game_model_callback, vector_pos) {}

    virtual ~Enemy() = default;

    int cost() const final { return Constants::ENEMY_COST; }

    bool is_friendly() const final { return false; }
};


#endif //WARP_ENEMY_H
