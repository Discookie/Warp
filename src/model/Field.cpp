#include "Field.h"

#include <utility>

#include "Stable/Factory.h"
#include "Stable/HqAttack.h"
#include "Stable/HqDefense.h"
#include "Stable/SniperTower.h"
#include "Stable/Special.h"
#include "model/Stable/LaserTower.h"
#include "model/Stable/TeslaCoil.h"

Field::Field(Coordinate position, std::shared_ptr<FieldEntityCallback> game_model_callback)
    : position(position),
      callback(std::move(game_model_callback)),
      team_status(Team::Neutral),
      tower(nullptr),
      moving_entities(std::vector<std::shared_ptr<Unstable>>()) {}

void Field::build_tower(EntityType type) {
    if (this->team_status == Team::Enemy) {
        throw std::exception();
    }
    if (this->tower) {
        throw std::exception();
    }
    switch (type) {
        case EntityType::TypeFactory:
            this->tower = std::make_shared<Factory>(this->position, this->callback);
            break;
        case EntityType::TypeLaserTower:
            this->tower = std::make_shared<LaserTower>(this->position, this->callback);
            break;
        case EntityType::TypeTeslaCoil:
            this->tower = std::make_shared<TeslaCoil>(this->position, this->callback);
            break;
        case EntityType::TypeSniperTower:
            this->tower = std::make_shared<SniperTower>(this->position, this->callback);
            break;
        case EntityType::TypeHqAttack:
            this->tower = std::make_shared<HqAttack>(this->position, this->callback);
            break;
        case EntityType::TypeHqDefense:
            this->tower = std::make_shared<HqDefense>(this->position, this->callback);
            break;
        case EntityType::TypeSpecial:
            this->tower = std::make_shared<Special>(this->position, this->callback);
            break;
        default:
            return;
    }
    this->team_status = Team::Friendly;
}

void Field::upgrade_tower() {
    if (!this->tower) {
        throw std::exception();
    }
    if (this->tower->is_upgraded()) {
        throw std::exception();
    }
    if (tower) this->tower->upgrade();
}

void Field::remove_tower() {
    if (!this->tower) {
        throw std::exception();
    }
    this->tower = nullptr;
    if (this->moving_entities.empty()) {
        this->team_status = Team::Neutral;
    }
}

std::shared_ptr<Stable> Field::get_tower() { return this->tower; }

void Field::add_moving_entity(std::shared_ptr<Unstable> obj) {
    this->moving_entities.push_back(obj);
}

void Field::remove_entity_at(int ind) {
    this->moving_entities.erase(this->moving_entities.begin() + ind);
    for (int i = 0; i < this->moving_entities.size(); i++) {
        moving_entities[i]->set_vector_pos(i);
    }
}

std::vector<std::shared_ptr<Unstable>> Field::get_moving_entities() {
    return this->moving_entities;
}

void Field::update_entities() {
    if (this->tower) {
        this->tower->update();
    }
    for (auto &me : this->moving_entities) {
        me->update();
    }
}
