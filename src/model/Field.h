#ifndef WARP_FIELD_H
#define WARP_FIELD_H

#include <memory>
#include <vector>
#include <optional>

#include "CallbackClass.h"
#include "Stable/Stable.h"
#include "Stable/Factory.h"
#include "model/Stable/LaserTower.h"
#include "Stable/HqAttack.h"
#include "Stable/HqDefense.h"
#include "Stable/Special.h"

#include "Unstable/Unstable.h"

#include "Team.h"
#include "EntityType.h"

class Field {
private:
    std::pair<int, int> position;
    CallbackClass callback;
    std::shared_ptr<Stable> tower;
    std::vector<std::shared_ptr<Unstable>> movingEntities;
    Team teamStatus;
public:
    Field() = default;
    explicit Field(std::pair<int, int> position, CallbackClass gameModelCallback);
    void buildTower(EntityType type);
    void upgradeTower();
    void removeTower();
    std::shared_ptr<Stable> getTower();
    std::vector<std::shared_ptr<Unstable>> getMovingEntities();
    Team getTeamStatus() const { return teamStatus; }
    void updateEntities();
};

#endif //WARP_FIELD_H
