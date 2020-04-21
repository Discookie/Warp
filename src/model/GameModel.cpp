#include "GameModel.h"

void GameModel::construct_fields() {
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 10; j++) {
            this->fields[i][j] = Field({i, j}, this->call_backs);
        }
    }
}

bool GameModel::valid_position(Coordinate position) const {
    return (0 <= position.x && position.x < 12) &&
           (0 <= position.y && position.y < 10);
}

Field &GameModel::get_field(Coordinate position) {
    if (!this->valid_position(position)) { throw std::invalid_argument("Out-of-range coordinates"); }
    return this->fields[position.x][position.y];
}

void GameModel::update_model() {
    this->update_fields();
    if (this->check_win()) {
        this->game_over = true;
    }
    if (this->check_lose()) {
        this->game_over = true;
    }
    this->time_counter++;
    this->wave_timer--;
    if (Constants::WAVE_SPAWN_TIME_START >= this->wave_timer && this->wave_timer <= Constants::WAVE_SPAWN_TIME_END) {
        this->spawn_wave();
    }
    if (this->wave_timer == Constants::WAVE_OVER_TIME) {
        this->wave_timer = Constants::WAVE_COUNTDOWN_TIME;
        this->wave_number++;
    }
    if (this->time_counter % Constants::GOLD_GEN_SPEED) {
        this->gold += Constants::GOLD_GEN_AMOUNT;
    }
    if (this->time_counter % Constants::SPAWN_ENEMIES_TIME) {
        this->spawn_enemies();
    }
}

void GameModel::update_fields() {
    for (auto &v : this->fields) {
        for (auto &f : v) {
            f.update_entities();
        }
    }
}

bool GameModel::check_win() const {
    return this->wave_number >= Constants::FINAL_WAVE_NUMBER;
}

bool GameModel::check_lose() const {
    for (const auto &a: this->fields) {
        if (a[0].get_team_status() == Team::Enemy) {
            return true;
        }
    }
    return false;
}

void GameModel::spawn_enemies() {

}

void GameModel::spawn_wave() {

}

void GameModel::init_callbacks() {
    // Produce Callback
    auto pro = [this](const std::shared_ptr<FieldEntity> &obj) {
        this->gold += std::static_pointer_cast<Factory>(obj)->production_amount();
    };
    // Move Callback
    auto mov = [this](const std::shared_ptr<FieldEntity> &obj) {
        std::optional<Coordinate> new_pos = std::static_pointer_cast<Unstable>(obj)->move_to(this->fields);
        if (!new_pos) { return; } // Can't move
        if (!this->valid_position(new_pos.value())) { throw std::invalid_argument("Out-of-range coordinates"); }
        int vec_pos = obj->get_vector_pos();
        if (vec_pos == -1) {
            throw std::invalid_argument("Tower entity can not move");
        }
        Coordinate pos = obj->get_position();
        this->get_field(pos).remove_entity_at(vec_pos);
        this->get_field(*new_pos).add_moving_entity(std::static_pointer_cast<Unstable>(obj));
    };
    // Attack Callback
    auto att = [this](const std::shared_ptr<FieldEntity> &obj) {
        obj->attack_entities(this->fields);
    };
    // Die Callback
    auto die = [this](const std::shared_ptr<FieldEntity> &obj) {
        if (obj->get_vector_pos() == -1) {
            this->get_field(obj->get_position()).remove_tower();
        } else {
            this->get_field(obj->get_position()).remove_entity_at(obj->get_vector_pos());
        }
    };
    call_backs = std::make_shared<FieldEntityCallback>(pro, mov, att, die);
}

GameModel::GameModel() {
    this->fields = std::vector(12, std::vector<Field>(10));
    GameModel::init_callbacks();
    GameModel::new_game();
}

void GameModel::new_game() {
    this->points = 0;
    this->gold = Constants::STARTING_GOLD;
    this->time_counter = 0;
    this->wave_number = 0;
    this->wave_timer = Constants::WAVE_COUNTDOWN_TIME;
    this->have_special = false;
    this->selected_tower = EntityType::TypeNone;
    this->construct_fields();
}

void GameModel::load_game() {
    throw std::logic_error("Unimplemented");
}

void GameModel::save_game() {
    throw std::logic_error("Unimplemented");
}

const Field &GameModel::get_field_const(Coordinate position) const {
    if (!this->valid_position(position)) { throw std::invalid_argument("Out-of-range coordinates"); }
    return this->fields[position.x][position.y];
}

void GameModel::update() {
    this->update_model();
}

void GameModel::select_tower(EntityType type) {
    this->selected_tower = type;
}

bool GameModel::is_buildable(EntityType type) const {
    switch (type) {
        case EntityType::TypeFactory:
            return this->gold >= Constants::FACTORY_BASE_COST;
        case EntityType::TypeLaserTower:
            return this->gold >= Constants::LASERTOWER_BASE_COST;
        case EntityType::TypeTeslaCoil:
            return this->gold >= Constants::TESLACOIL_BASE_COST;
        case EntityType::TypeSniperTower:
            return this->gold >= Constants::SNIPERTOWER_BASE_COST;
        case EntityType::TypeHqAttack:
            return this->gold >= Constants::HQATTACK_BASE_COST;
        case EntityType::TypeHqDefense:
            return this->gold >= Constants::HQDEFENSE_BASE_COST;
        case EntityType::TypeSpecial:
            return this->gold >= Constants::SPECIAL_BASE_COST &&
                   this->have_special;
        default: return false;
    }
}

void GameModel::build_tower(Coordinate position) {
    if (!this->valid_position(position)) { throw std::invalid_argument("Out-of-range coordinates"); }
    if (this->get_field(position).get_tower()) { throw std::invalid_argument("Tower space occupied"); }
    if (!this->is_buildable(selected_tower)) { throw std::invalid_argument("Insufficient gold"); }
    if (this->get_field(position).get_team_status() == Team::Enemy) { throw std::invalid_argument("Enemy territory"); }

    this->get_field(position).build_tower(selected_tower);
    this->gold -= get_field(position).get_tower()->cost();
    this->points += Constants::POINTS_FOR_TOWER_BUILD;
}

void GameModel::upgrade_tower(Coordinate position) {
    if (!this->valid_position(position)) { throw std::invalid_argument("Out-of-range coordinates"); }
    if (!this->get_field(position).get_tower()) { throw std::invalid_argument("No tower to upgrade"); }
    if (this->get_field(position).get_tower()->is_upgraded()) { throw std::invalid_argument("Tower already upgraded"); }
    if (this->gold < get_field(position).get_tower()->upgrade_cost()) {
        throw std::invalid_argument("Insufficient gold");
    }

    this->gold -= get_field(position).get_tower()->upgrade_cost();
    get_field(position).upgrade_tower();
    this->points += Constants::POINTS_FOR_TOWER_UPGRADE;
}

void GameModel::remove_tower(Coordinate position) {
    if (!this->valid_position(position)) { throw std::invalid_argument("Out-of-range coordinates"); }
    if (!this->get_field(position).get_tower()) { throw std::invalid_argument("No tower to remove"); }

    this->gold += this->get_field(position).get_tower()->remove_value();
    this->get_field(position).remove_tower();
    this->points -= Constants::POINTS_FOR_TOWER_REMOVE;
}
