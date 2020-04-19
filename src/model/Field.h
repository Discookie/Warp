#ifndef WARP_FIELD_H
#define WARP_FIELD_H

#include <memory>
#include <vector>
#include <optional>

#include "FieldEntityCallbackClass.h"
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
    Coordinate position;
    std::shared_ptr<FieldEntityCallbackClass> callback;
    std::shared_ptr<Stable> tower;
    std::vector<std::shared_ptr<Unstable>> movingEntities;
    Team teamStatus = Team::Neutral;
public:
    Field() = default;

    explicit Field(Coordinate position, const std::shared_ptr<FieldEntityCallbackClass> &gameModelCallback);

    // Stable
    void buildTower(EntityType type);
    void upgradeTower();
    void removeTower();
    std::shared_ptr<Stable> getTower();

    // Unstable
    /// This is supposed to be called only by die() callback
    void removeEntityAt(int ind);
    std::vector<std::shared_ptr<Unstable>> getMovingEntities();

    // General
    Team getTeamStatus() const { return teamStatus; }
    void updateEntities();
};

#endif //WARP_FIELD_H
