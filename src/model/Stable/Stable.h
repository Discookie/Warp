#ifndef WARP_STABLE_H
#define WARP_STABLE_H

#include "../FieldEntity.h"

class Stable : public FieldEntity {
protected:
    bool upgraded;
public:
    virtual ~Stable() = default;

    bool isFriendly() final { return true; }
    int getVectorPos() final { return -1; }
    void upgrade() { upgraded = true; };
    bool isUpgraded() { return upgraded; };
    virtual int removeValue() = 0;
};


#endif //WARP_STABLE_H
