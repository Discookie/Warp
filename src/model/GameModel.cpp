#include "GameModel.h"

GameModel::GameModel(){
    this->fields = std::vector(12, std::vector<Field>(10));
    GameModel::init_callbacks();
    GameModel::new_game();
}

void GameModel::new_game(){
    this->fields.clear();
    this->points = 0;
    this->gold = 0;
    this->wave_timer = 2000;
    this->have_special = false;
    this->selected_tower = EntityType::TypeNone;
    this->construct_fields();
}

void GameModel::init_callbacks() {
    // Produce Callback
    auto pro = [this](const std::shared_ptr<FieldEntity>& obj) {
        this->gold += std::static_pointer_cast<Factory>(obj)->production_amount();
    };
    // Move Callback
    auto mov = [this](const std::shared_ptr<FieldEntity>& obj) {
        std::optional<Coordinate> new_pos = std::static_pointer_cast<Unstable>(obj)->move_to(fields);
        if (!new_pos) {
            return; // Can't move
        }
        int vec_pos = obj->get_vector_pos();
        Coordinate pos = obj->get_position();
        if (vec_pos == -1) {
            return; // Thorw sg
        }
        this->get_field(pos).remove_entity_at(vec_pos);
        this->get_field(*new_pos).add_moving_entity(std::static_pointer_cast<Unstable>(obj));
    };
    // Attack Callback
    auto att = [this](const std::shared_ptr<FieldEntity>& obj) {
        obj->attack_entities(fields);
    };
    // Die Callback
    auto die = [this](const std::shared_ptr<FieldEntity>& obj) {
        if(obj->get_vector_pos() == -1) {
            this->get_field(obj->get_position()).remove_tower();
        }
        else{
            this->get_field(obj->get_position()).remove_entity_at(obj->get_vector_pos());
        }
    };
    call_backs = std::make_shared<FieldEntityCallback>(pro, mov, att, die);
}

void GameModel::load_game() {
    throw std::logic_error("Unimplemented");
}

void GameModel::construct_fields() {
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 10; j++) {
            this->fields[i][j] = Field({i, j}, this->call_backs);
        }
    }
}

Field &GameModel::get_field(Coordinate position) {
    if ((0 <= position.x && position.x < 12) &&
        (0 <= position.y && position.y < 10)) {
        return this->fields[position.x][position.y];
    }
    throw std::exception();
}

void GameModel::update_model() {
    this->update_fields();

}

void GameModel::update_fields() {
    for(auto& v : this->fields){
        for(auto& f : v){
            f.update_entities();
        }
    }
}

void GameModel::select_tower(EntityType type) {
    this->selected_tower = type;
}

bool GameModel::is_buildable(EntityType type) {
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
    if (is_buildable(selected_tower) &&
        !get_field(position).get_tower() &&
            get_field(position).get_team_status() != Team::Enemy
            ) {
        get_field(position).build_tower(selected_tower);
        this->gold -= get_field(position).get_tower()->cost();
        // this->points += 100;
    } else {
        // You can't build here!
    }
}

void GameModel::upgrade_tower(Coordinate position) {
    if (get_field(position).get_tower() && !get_field(position).get_tower()->is_upgraded()) {
        if (this->gold >= get_field(position).get_tower()->upgrade_cost()) {
            this->gold -= get_field(position).get_tower()->upgrade_cost();
            get_field(position).upgrade_tower();
        }
    }
}

int GameModel::get_wave_progress() {
    throw std::logic_error("Unimplemented");
}

/*
void GameModel::pause() {
    al_stop_timer(this->timer);
}

void GameModel::resume() {
    al_resume_timer(this->timer);
}
*/