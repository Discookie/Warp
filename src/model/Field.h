#ifndef WARP_FIELD_H
#define WARP_FIELD_H

#include <memory>
#include <vector>
#include <optional>

#include "Stable/Stable.h"
#include "Unstable/Unstable.h"

#include "Team.h"
#include "EntityType.h"

class Field {
private:
    std::pair<int, int> position;
    std::optional<std::shared_ptr<Stable>> tower;
    std::vector<std::shared_ptr<Unstable>> movingEntities;
    Team teamStatus;
public:
    Field(){}
    explicit Field(std::pair<int, int> position);
    void buildTower(EntityType type);
    void removeTower();
    std::optional<std::shared_ptr<Stable>> getTower();
    std::vector<std::shared_ptr<Unstable>> getMovingEntities();
    Team getTeamStatus() const { return teamStatus; }
    void updateEntities();
};

#endif //WARP_FIELD_H
