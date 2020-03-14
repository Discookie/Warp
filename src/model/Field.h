#ifndef WARP_FIELD_H
#define WARP_FIELD_H

#include <memory>
#include <vector>

#include "Stable/Stable.h"
#include "Unstable/Unstable.h"
#include "Team.h"

class Field {
private:
    std::unique_ptr<Stable> tower;
    std::vector<std::unique_ptr<Unstable>> movingEntities;
    Team teamStatus;
public:
    void updateEntities();
};

#endif //WARP_FIELD_H
