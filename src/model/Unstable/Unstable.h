#ifndef WARP_UNSTABLE_H
#define WARP_UNSTABLE_H

#include "../FieldEntity.h"

class Unstable : public FieldEntity {
protected:
    int speed;
public:
    virtual ~Unstable() = default;
    virtual void move() = 0;
};


#endif //WARP_UNSTABLE_H
