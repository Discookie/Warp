#include "GameModel.h"

#include <windows.h>

#include <fstream>

#include "Stable/Factory.h"

void GameModel::construct_fields() {
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 10; j++) {
            this->fields[i][j] = Field({i, j}, this->call_backs);
        }
    }
}

bool GameModel::valid_position(Coordinate position) const {
    return (0 <= position.x && position.x < 12) && (0 <= position.y && position.y < 10);
}

Field &GameModel::get_field(Coordinate position) {
    if (!this->valid_position(position)) {
        throw std::invalid_argument("Out-of-range coordinates");
    }
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
    if (Constants::WAVE_SPAWN_TIME_START >= this->wave_timer
        && this->wave_timer <= Constants::WAVE_SPAWN_TIME_END) {
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

bool GameModel::check_win() const { return this->wave_number >= Constants::FINAL_WAVE_NUMBER; }

bool GameModel::check_lose() const {
    for (const auto &a : this->fields) {
        if (a[0].get_team_status() == Team::TeamEnemy) {
            return true;
        }
    }
    return false;
}

void GameModel::spawn_enemies() {}

void GameModel::spawn_wave() {}

void GameModel::init_callbacks() {
    // Produce Callback
    auto pro = [this](const std::shared_ptr<FieldEntity> &obj) {
        this->gold += std::static_pointer_cast<Factory>(obj)->production_amount();
    };
    // Move Callback
    auto mov = [this](const std::shared_ptr<FieldEntity> &obj) {
        std::optional<Coordinate> new_pos =
            std::static_pointer_cast<Unstable>(obj)->move_to(this->fields);
        if (!new_pos) {
            return;
        }  // Can't move
        if (obj->get_vector_pos() == -1) {
            throw std::invalid_argument("Tower entity can not move");
        }
        this->get_field(obj->get_position()).remove_entity_at(obj->get_vector_pos());
        if (new_pos->x != -1 && new_pos->y != -1) {
            if (!this->valid_position(new_pos.value())) {
                throw std::invalid_argument("Out-of-range coordinates");
            }
            this->get_field(*new_pos).add_moving_entity(std::static_pointer_cast<Unstable>(obj));
        }
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
    this->points         = 0;
    this->gold           = Constants::STARTING_GOLD;
    this->time_counter   = 0;
    this->wave_number    = 0;
    this->wave_timer     = Constants::WAVE_COUNTDOWN_TIME;
    this->have_special   = false;
    this->selected_tower = EntityType::TypeNone;
    this->game_over      = false;
    this->construct_fields();
}

void GameModel::load_game(const std::string &file_name) {
    std::fstream fs;
    fs.open(file_name, std::fstream::in);

    fs >> *this;

    fs.close();
}

void GameModel::save_game(const std::string &file_name) const {
    std::fstream fs;
    fs.open(file_name, std::fstream::out | std::fstream::trunc);

    fs << *this;

    fs.close();
}

std::string GameModel::get_file_name() const {
    char filename[MAX_PATH];

    OPENFILENAME ofn;
    ZeroMemory(&filename, sizeof(filename));
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner   = nullptr;  // If you have a window to center over, put its HANDLE here
    ofn.lpstrFilter = "Text Files\0*.txt\0Any File\0*.*\0";
    ofn.lpstrFile   = filename;
    ofn.nMaxFile    = MAX_PATH;
    ofn.lpstrTitle  = "Select a File, yo!";
    ofn.Flags       = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

    if (GetOpenFileNameA(&ofn)) {
        return std::string(filename);
    } else {
        throw std::invalid_argument("Error during file open");
    }
}

void GameModel::load_game() {
    try {
        load_game(get_file_name());
    }
    catch (std::exception& e) {

    }
}

void GameModel::save_game() const {
    try {
        save_game(get_file_name());
    }
    catch (std::exception& e) {

    }
}

const Field &GameModel::get_field_const(Coordinate position) const {
    if (!this->valid_position(position)) {
        throw std::invalid_argument("Out-of-range coordinates");
    }
    return this->fields[position.x][position.y];
}

void GameModel::update() { this->update_model(); }

void GameModel::select_tower(EntityType type) { this->selected_tower = type; }

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
            return this->gold >= Constants::SPECIAL_BASE_COST && this->have_special;
        default:
            return false;
    }
}

void GameModel::build_tower(Coordinate position) {
    if (!this->valid_position(position)) {
        throw std::invalid_argument("Out-of-range coordinates");
    }
    if (this->get_field(position).get_tower()) {
        throw std::invalid_argument("Tower space occupied");
    }
    if (!this->is_buildable(selected_tower)) {
        throw std::invalid_argument("Insufficient gold");
    }
    if (this->get_field(position).get_team_status() == Team::TeamEnemy) {
        throw std::invalid_argument("TeamEnemy territory");
    }

    this->get_field(position).build_tower(selected_tower);
    this->gold -= get_field(position).get_tower()->cost();
    this->points += Constants::POINTS_FOR_TOWER_BUILD;
}

void GameModel::upgrade_tower(Coordinate position) {
    if (!this->valid_position(position)) {
        throw std::invalid_argument("Out-of-range coordinates");
    }
    if (!this->get_field(position).get_tower()) {
        throw std::invalid_argument("No tower to upgrade");
    }
    if (this->get_field(position).get_tower()->is_upgraded()) {
        throw std::invalid_argument("Tower already upgraded");
    }
    if (this->gold < get_field(position).get_tower()->upgrade_cost()) {
        throw std::invalid_argument("Insufficient gold");
    }

    this->gold -= get_field(position).get_tower()->upgrade_cost();
    get_field(position).upgrade_tower();
    this->points += Constants::POINTS_FOR_TOWER_UPGRADE;
}

void GameModel::remove_tower(Coordinate position) {
    if (!this->valid_position(position)) {
        throw std::invalid_argument("Out-of-range coordinates");
    }
    if (!this->get_field(position).get_tower()) {
        throw std::invalid_argument("No tower to remove");
    }

    this->gold += this->get_field(position).get_tower()->remove_value();
    this->get_field(position).remove_tower();
    this->points -= Constants::POINTS_FOR_TOWER_REMOVE;
}

std::ostream &operator<<(std::ostream &os, const GameModel &model) {
    os << model.points << "\n"
       << model.gold << "\n"
       << model.time_counter << "\n"
       << model.wave_timer << "\n"
       << model.wave_number << "\n"
       << model.have_special << "\n"
       << model.selected_tower << "\n"
       << model.game_over << "\n";
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 10; ++j) {
            os << model.fields[i][j] << "\n";
        }
    }
    return os;
}

std::istream &operator>>(std::istream &is, GameModel &model) {
    int selected_tower_buffer;
    model.fields = std::vector(12, std::vector<Field>(10));
    model.init_callbacks();
    model.construct_fields();
    is >> model.points >> model.gold >> model.time_counter >> model.wave_timer >> model.wave_number
        >> model.have_special >> selected_tower_buffer >> model.game_over;
    model.selected_tower = (EntityType)selected_tower_buffer;
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 10; ++j) {
            is >> model.fields[i][j];
        }
    }
    return is;
}

bool GameModel::operator==(const GameModel &rhs) const {
    return fields == rhs.fields && points == rhs.points && gold == rhs.gold
           && time_counter == rhs.time_counter && wave_timer == rhs.wave_timer
           && wave_number == rhs.wave_number && have_special == rhs.have_special
           && selected_tower == rhs.selected_tower && game_over == rhs.game_over;
}

bool GameModel::operator!=(const GameModel &rhs) const { return !(rhs == *this); }
