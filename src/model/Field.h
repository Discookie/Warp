#ifndef WARP_FIELD_H
#define WARP_FIELD_H

#include <memory>
#include <optional>
#include <vector>

#include "EntityType.h"
#include "FieldEntityCallback.h"
#include "Stable/Factory.h"
#include "Stable/HqAttack.h"
#include "Stable/HqDefense.h"
#include "Stable/Special.h"
#include "Stable/Stable.h"
#include "Team.h"
#include "Unstable/Unstable.h"
#include "model/Stable/LaserTower.h"

class Field {
private:
    Coordinate position{};
    std::shared_ptr<FieldEntityCallback> callback;
    std::shared_ptr<Stable> tower;
    std::vector<std::shared_ptr<Unstable>> moving_entities;
    Team team_status = Team::Neutral;

public:
    Field() = default;

    explicit Field(Coordinate position, std::shared_ptr<FieldEntityCallback> game_model_callback);

    // Stable
    void build_tower(EntityType type);
    void upgrade_tower();
    void remove_tower();
    std::shared_ptr<Stable> get_tower();

    // Unstable
    void add_moving_entity(std::shared_ptr<Unstable> obj);

    /// This is supposed to be called only by die() callback
    void remove_entity_at(int ind);
    std::vector<std::shared_ptr<Unstable>> get_moving_entities();

    // General
    Team get_team_status() const { return team_status; }
    void update_entities();
};

#endif  // WARP_FIELD_H
