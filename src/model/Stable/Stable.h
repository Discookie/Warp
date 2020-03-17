#ifndef WARP_STABLE_H
#define WARP_STABLE_H

#include "../FieldEntity.h"

class Stable : public FieldEntity{
protected:
    bool isUpgraded;
public:
    virtual ~Stable() = default;

    virtual void upgrade() = 0;
    virtual int value() = 0;
};


#endif //WARP_STABLE_H
