#ifndef WARP_STABLE_H
#define WARP_STABLE_H

#include "../FieldEntity.h"

class Stable : public FieldEntity {
protected:
    bool isUpgraded;
public:
    virtual ~Stable() = default;

    void upgrade() { isUpgraded = true; };
    bool getIsUpgraded() { return isUpgraded; };
    virtual int removeValue() = 0;
};


#endif //WARP_STABLE_H
