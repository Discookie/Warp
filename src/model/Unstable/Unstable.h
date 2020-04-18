#ifndef WARP_UNSTABLE_H
#define WARP_UNSTABLE_H

#include "../FieldEntity.h"

class Unstable : public FieldEntity {
public:
    virtual int speed() = 0;

    ~Unstable() override = default;

    virtual void move() = 0;

    // should set this->position to the new position, and return it
    // should only be called by move callback
    // if cant move, should return {}
    virtual std::optional<Coordinate> move_to(const std::vector<std::vector<Field>>&) = 0;
};

#endif  // WARP_UNSTABLE_H
