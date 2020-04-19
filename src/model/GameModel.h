#ifndef WARP_GAMEMODEL_H
#define WARP_GAMEMODEL_H

#include <vector>
#include <functional>

#include "Field.h"
#include "EntityType.h"
#include "FieldEntityCallbackClass.h"

#include "Stable/Factory.h"
#include "model/Stable/LaserTower.h"
#include "Stable/HqAttack.h"
#include "Stable/HqDefense.h"
#include "Stable/Special.h"
#include "Stable/TeslaCoil.h"
#include "Stable/SniperTower.h"

class GameModel {
private:
    std::vector<std::vector<Field>> fields;
    int points;
    int gold;
    int wave_timer;
    int wave_number;
    bool have_special;
    EntityType selected_tower;
    // Callbacks
    std::shared_ptr<FieldEntityCallbackClass> call_backs;
    void init_callbacks();
public:
    // Constructors
    GameModel();

    void new_game();

    void load_game();

    void construct_fields();

    // Updates
    void update_model();

    void update_fields();

    // Building (player interaction)
    void select_tower(EntityType type);

    void build_tower(Coordinate position);

    void upgrade_tower(Coordinate position);

    // Enemy interaction
    void spawn_enemies();

    // Getters
    Field &get_field(Coordinate position);

    int get_gold() const { return this->gold; }

    int get_points() const { return this->points; }

    int get_wave_number() const { return this->wave_number; }

    int get_wave_progress();
    bool is_buildable(EntityType type);
};

#endif //WARP_GAMEMODEL_H
