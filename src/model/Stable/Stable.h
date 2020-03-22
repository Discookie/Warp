#ifndef WARP_STABLE_H
#define WARP_STABLE_H

#include "../FieldEntity.h"

class Stable : public FieldEntity {
protected:
    bool isUpgraded;
public:
    virtual ~Stable() = default;

    bool isFriendly() final { return true; }
    void upgrade() { isUpgraded = true; };
    bool getIsUpgraded() { return isUpgraded; };
    virtual int removeValue() = 0;
};


#endif //WARP_STABLE_H
