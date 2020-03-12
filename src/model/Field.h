#ifndef WARP_FIELD_H
#define WARP_FIELD_H

#include "Stable/Stable.h"
#include "Unstable/Unstable.h"
#include "Team.h"
#include <vector>

class Field {
private:
    Stable tower;
    std::vector<Unstable> movingEntities;
    Team teamStatus;
public:
    void updateEntities();
};


#endif //WARP_FIELD_H
