#ifndef WARP_UNSTABLE_H
#define WARP_UNSTABLE_H

#include "../FieldEntity.h"

class Unstable : public FieldEntity {
public:
    virtual int speed() = 0;
    virtual ~Unstable() = default;
    virtual void move() = 0;
};


#endif //WARP_UNSTABLE_H
