#ifndef WARP_GAMEMODEL_H
#define WARP_GAMEMODEL_H

#include <functional>
#include <iostream>
#include <vector>
#include <cstdlib>

#include "Difficulty.h"
#include "EntityType.h"
#include "Field.h"
#include "FieldEntityCallback.h"

class GameModel {
private:
    std::vector<std::vector<Field>> fields;
    int points;
    int gold;
    int time_counter;
    int wave_timer;
    int wave_number;
    bool have_special;
    EntityType selected_tower;
    bool game_over;
    Difficulty diff;

    // Helpers
    void construct_fields();

    bool valid_position(Coordinate position) const;

    Field &get_field(Coordinate position);

    void update_model();

    void update_fields();

    bool check_win() const;

    bool check_lose() const;

    // TeamEnemy interaction
    void spawn_enemies();

    void spawn_wave();

    // Callbacks
    std::shared_ptr<FieldEntityCallback> call_backs;

    void init_callbacks();

public:
    GameModel();

    void new_game();

    // Persistence
    void load_game(const std::string &file_name);

    void save_game(const std::string &file_name) const;

    std::string get_file_name() const;

    void load_game();

    void save_game() const;
    // Updates
    void update();


    // Building (player interaction)
    void select_tower(EntityType type);

    void build_tower(Coordinate position);

    void upgrade_tower(Coordinate position);

    void remove_tower(Coordinate position);

    // Getters
    const Field &get_field_const(Coordinate position) const;

    int get_gold() const { return this->gold; }

    int get_points() const { return this->points; }

    int get_wave_number() const { return this->wave_number; }

    int get_wave_progress() const { return this->wave_timer; }

    bool is_buildable(EntityType type) const;

    bool is_game_over() const { return game_over; }

    friend std::ostream &operator<<(std::ostream &os, const GameModel &model);

    friend std::istream &operator>>(std::istream &is, GameModel &model);

    bool operator==(const GameModel &rhs) const;

    bool operator!=(const GameModel &rhs) const;
};

#endif //WARP_GAMEMODEL_H
