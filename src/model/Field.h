#ifndef WARP_FIELD_H
#define WARP_FIELD_H

#include <iostream>
#include <memory>
#include <optional>
#include <vector>

#include "EntityType.h"
#include "FieldEntityCallback.h"
#include "Stable/Stable.h"
#include "Team.h"
#include "Unstable/Unstable.h"

class Field {
private:
    Coordinate position{};
    std::shared_ptr<FieldEntityCallback> callback;
    std::shared_ptr<Stable> tower;
    std::vector<std::shared_ptr<Unstable>> moving_entities;
    Team team_status = Team::TeamNeutral;

    int add_unstable(EntityType et);

public:
    Field() = default;

    explicit Field(Coordinate position, std::shared_ptr<FieldEntityCallback> game_model_callback);

    Coordinate get_position() const { return position; }

    // Stable
    void build_tower(EntityType type);

    void upgrade_tower();

    void remove_tower();

    std::shared_ptr<Stable> get_tower();

    std::shared_ptr<const Stable> get_tower_const() const;

    // Unstable
    void spawn_moving_entity(EntityType type);

    void add_moving_entity(std::shared_ptr<Unstable> obj);

    /// This is supposed to be called only by die() callback
    bool remove_entity_at(int ind);

    std::vector<std::shared_ptr<Unstable>> get_moving_entities();

    std::vector<std::shared_ptr<const Unstable>> get_moving_entities_const() const;

    // General
    Team get_team_status() const { return team_status; }

    void update_entities();

    friend std::ostream& operator<<(std::ostream& os, const Field& field);

    friend std::istream& operator>>(std::istream& is, Field& field);

    bool operator==(const Field& rhs) const;

    bool operator!=(const Field& rhs) const;
};

#endif  // WARP_FIELD_H
