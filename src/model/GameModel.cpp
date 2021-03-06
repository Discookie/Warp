#include "GameModel.h"

#include "Constants.h"
#include <windows.h>
#include <fstream>
#include <model/Stable/Factory.h>
#include <cmath>
#include <ctime>

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
    if (this->time_counter % Constants::GOLD_GEN_SPEED == 0) {
        this->gold += Constants::GOLD_GEN_AMOUNT;
    }
    this->spawn_enemies();
}

void GameModel::update_fields() {
    for (auto &v : this->fields) {
        for (auto &f : v) {
            f.update_entities();
        }
    }
}

bool GameModel::check_win() const { return this->wave_number >= Constants::FINAL_WAVE_NUMBER(); }

bool GameModel::check_lose() const {
    for (const auto &a : this->fields[0]) {
        if (a.get_team_status() == Team::TeamEnemy) {
            return true;
        }
    }
    return false;
}

void GameModel::spawn_enemies() {
    int r = std::rand();
    if (time_counter < Constants::WAVE_COUNTDOWN_TIME) {
        if (r % int(Constants::ALIEN_SPWN_BASE_FREQUENCY * std::pow(0.6, this->wave_number)) == 0) {
            int y = std::rand() % 10;
            this->fields[11][y].spawn_moving_entity(EntityType::TypeAlien);
        }
    } else if (time_counter < Constants::WAVE_COUNTDOWN_TIME * 2) {
        if (r % int(Constants::ALIEN_SPWN_BASE_FREQUENCY * std::pow(0.6, this->wave_number)) == 0) {
            int y = std::rand() % 10;
            this->fields[11][y].spawn_moving_entity(EntityType::TypeAlien);
        }
        if (r % int(Constants::OCTOPUS_SPWN_BASE_FREQUENCY * std::pow(0.6, this->wave_number)) == 0) {
            int y = std::rand() % 10;
            this->fields[11][y].spawn_moving_entity(EntityType::TypeOctopus);
        }
    } else {
        if (r % int(Constants::ALIEN_SPWN_BASE_FREQUENCY * std::pow(0.6, this->wave_number)) == 0) {
            int y = std::rand() % 10;
            this->fields[11][y].spawn_moving_entity(EntityType::TypeAlien);
        }
        if (r % int(Constants::OCTOPUS_SPWN_BASE_FREQUENCY * std::pow(0.6, this->wave_number)) == 0) {
            int y = std::rand() % 10;
            this->fields[11][y].spawn_moving_entity(EntityType::TypeOctopus);
        }
        if (r % int(Constants::ROBOT_SPWN_BASE_FREQUENCY * std::pow(0.6, this->wave_number)) == 0) {
            int y = std::rand() % 10;
            this->fields[11][y].spawn_moving_entity(EntityType::TypeRobot);
        }
    }
}

void GameModel::spawn_wave() {
    int r = std::rand();
    if (r % int(Constants::ALIEN_SPWN_WAVE_FREQUENCY * std::pow(0.6, this->wave_number)) == 0) {
        int y = std::rand() % 10;
        this->fields[11][y].spawn_moving_entity(EntityType::TypeAlien);
    }
    if (r % int(Constants::OCTOPUS_SPWN_WAVE_FREQUENCY * std::pow(0.6, this->wave_number)) == 0) {
        int y = std::rand() % 10;
        this->fields[11][y].spawn_moving_entity(EntityType::TypeOctopus);
    }
    if (r % int(Constants::ROBOT_SPWN_WAVE_FREQUENCY * std::pow(0.6, this->wave_number)) == 0) {
        int y = std::rand() % 10;
        this->fields[11][y].spawn_moving_entity(EntityType::TypeRobot);
    }
}

void GameModel::init_callbacks() {
    // Produce Callback
    auto pro = [this](std::shared_ptr<FieldEntity> obj) {
        this->gold += std::static_pointer_cast<Factory>(obj)->production_amount();
    };
    // Move Callback
    auto mov = [this](std::shared_ptr<FieldEntity> obj) {
        std::optional<Coordinate> new_pos =
            std::static_pointer_cast<Unstable>(obj)->move_to(this->fields);
        if (!new_pos) {
            return;
        }  // Can't move
        if (obj->get_vector_pos() == -1) {
            throw std::invalid_argument("Tower entity can not move");
        }
        auto &f = this->get_field(obj->get_position());
        auto p = obj->get_vector_pos();
        bool bug = f.remove_entity_at(p);
        if (new_pos->x != -1 && new_pos->y != -1) {
            if (!this->valid_position(new_pos.value())) {
                throw std::invalid_argument("Out-of-range coordinates");
            }
            obj->set_position(*new_pos);
            if (!bug)
                this->get_field(*new_pos).add_moving_entity(std::static_pointer_cast<Unstable>(obj));
        }
    };
    // Attack Callback
    auto att = [this](std::shared_ptr<FieldEntity> obj) {
        obj->attack_entities(this->fields);
    };
    // Die Callback
    auto die = [this](std::shared_ptr<FieldEntity> obj) {
        if (obj->get_vector_pos() == -1) {
            this->get_field(obj->get_position()).remove_tower();
        } else {
            if (obj->get_entity_type() == EntityType::TypeRobot) {
                this->have_special = true;
            }
            this->get_field(obj->get_position()).remove_entity_at(obj->get_vector_pos());
        }
    };
    call_backs = std::make_shared<FieldEntityCallback>(pro, mov, att, die);
}

GameModel::GameModel() {
    this->fields = std::vector(12, std::vector<Field>(10));
    GameModel::init_callbacks();
    GameModel::change_difficulty(Difficulty::DiffEasy);
    GameModel::new_game();
}

void GameModel::change_difficulty(Difficulty df) {
    switch (df) {
        case Difficulty::DiffEasy:
            Constants::diff = 1;
            break;
        case Difficulty::DiffNormal:
            Constants::diff = 1.2;
            break;
        case Difficulty::DiffHard:
            Constants::diff = 1.5;
            break;
        default:
            Constants::diff = 1;
            break;
    }
}

void GameModel::new_game() {
    std::srand(time(NULL));
    this->points = 0;
    this->gold = Constants::STARTING_GOLD;
    this->time_counter = 0;
    this->wave_number = 0;
    this->wave_timer = Constants::WAVE_COUNTDOWN_TIME;
    this->have_special = false;
    this->selected_tower = EntityType::TypeNone;
    this->game_over = false;
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

std::optional<std::string> GameModel::get_file_name(bool must_exist) const {
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
    if (must_exist)
        ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;
    else
        ofn.Flags = OFN_DONTADDTORECENT;

    if (GetOpenFileNameA(&ofn)) {
        return std::string(filename);
    } else {
        return {};
    }
}

bool GameModel::load_game() {
    try {
        std::optional<std::string> filename = get_file_name(true);
        if (filename) {
            load_game(*filename);
            return true;
        }
    }
    catch (std::exception& e) {
    }
    return false;
}

bool GameModel::save_game() const {
    try {
        std::optional<std::string> filename = get_file_name(false);
        if (filename) {
            save_game(*filename);
            return true;
        }
    }
    catch (std::exception& e) {
    }
    return false;
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
            return this->gold >= Constants::FACTORY_BASE_COST();
        case EntityType::TypeLaserTower:
            return this->gold >= Constants::LASERTOWER_BASE_COST();
        case EntityType::TypeTeslaCoil:
            return this->gold >= Constants::TESLACOIL_BASE_COST();
        case EntityType::TypeSniperTower:
            return this->gold >= Constants::SNIPERTOWER_BASE_COST();
        case EntityType::TypeHqAttack:
            return this->gold >= Constants::HQATTACK_BASE_COST();
        case EntityType::TypeHqDefense:
            return this->gold >= Constants::HQDEFENSE_BASE_COST();
        case EntityType::TypeSpecial:
            return this->gold >= Constants::SPECIAL_BASE_COST() && this->have_special;
        default:
            return false;
    }
}

std::optional<std::string> GameModel::add_friendly_entity(Coordinate position) {
    if (!this->valid_position(position)) {
        return "Out-of-range coordinates";
    }
    if (this->get_field(position).get_team_status() == Team::TeamEnemy) {
        return "Enemy territory";
    }
    if (selected_tower != EntityType::TypeFriendly) {
        return build_tower(position);
    }
    else {
        this->get_field(position).spawn_moving_entity(selected_tower);
        this->gold -= Constants::FRIENDLY_COST();
        // TODO: this->points += Constants::POINTS_FOR_FRIENDLY;
    }
    return {};
}

std::optional<std::string> GameModel::build_tower(Coordinate position) {
    if (this->selected_tower == EntityType::TypeNone) {
        return "No selected tower";
    }
    if (this->get_field(position).get_tower_const()) {
        return "Tower space occupied";
    }
    if (selected_tower == EntityType::TypeSpecial && !this->have_special) {
        return "Don't have special";
    }
    if (!this->is_buildable(selected_tower)) {
        return "Insufficient gold";
    }
    if (selected_tower == EntityType::TypeHqAttack || selected_tower == EntityType::TypeHqDefense) {
        if (position.x != 0) {
            return "You can't build HQ here";
        }
    } else {
        if (position.x == 0) {
            return "You can only build HQ here";
        }
    }

    this->get_field(position).build_tower(selected_tower);
    this->gold -= get_field(position).get_tower_const()->cost();
    this->points += Constants::POINTS_FOR_TOWER_BUILD;
    return {};
}

std::optional<std::string> GameModel::upgrade_tower(Coordinate position) {
    if (!this->valid_position(position)) {
        return "Out-of-range coordinates";
    }
    if (!this->get_field(position).get_tower_const()) {
        return "No tower to upgrade";
    }
    if (this->get_field(position).get_tower_const()->is_upgraded()) {
        return "Tower already upgraded";
    }
    if (this->gold < get_field(position).get_tower_const()->upgrade_cost()) {
        return "Insufficient gold";
    }

    this->gold -= get_field(position).get_tower_const()->upgrade_cost();
    get_field(position).upgrade_tower();
    this->points += Constants::POINTS_FOR_TOWER_UPGRADE;
    return {};
}

std::optional<std::string> GameModel::remove_tower(Coordinate position) {
    if (!this->valid_position(position)) {
        return "Out-of-range coordinates";
    }
    if (!this->get_field(position).get_tower_const()) {
        return "No tower to remove";
    }

    this->gold += this->get_field(position).get_tower_const()->remove_value();
    this->get_field(position).remove_tower();
    this->points -= Constants::POINTS_FOR_TOWER_REMOVE;
    return {};
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
