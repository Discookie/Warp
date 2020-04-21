#include "Field.h"

#include <utility>

#include "Stable/Factory.h"
#include "Stable/HqAttack.h"
#include "Stable/HqDefense.h"
#include "Stable/SniperTower.h"
#include "Stable/Special.h"
#include "Stable/LaserTower.h"
#include "Stable/TeslaCoil.h"
#include "Unstable/Alien.h"
#include "Unstable/Friendly.h"
#include "Unstable/Octopus.h"
#include "Unstable/Robot.h"

Field::Field(Coordinate position, std::shared_ptr<FieldEntityCallback> game_model_callback)
    : position(position),
      callback(std::move(game_model_callback)),
      team_status(Team::TeamNeutral),
      tower(nullptr),
      moving_entities(std::vector<std::shared_ptr<Unstable>>()) {}

int Field::add_unstable(EntityType et) {
    switch (et) {
        case TypeAlien:
            moving_entities.push_back(std::make_shared<Alien>(
                Alien(position, callback, moving_entities.size())));
            break;
        case TypeOctopus:
            moving_entities.push_back(
                std::make_shared<Octopus>(Octopus(position, callback, moving_entities.size())));
            break;
        case TypeRobot:
            moving_entities.push_back(
                std::make_shared<Robot>(Robot(position, callback, moving_entities.size())));
            break;
        case TypeFriendly:
            moving_entities.push_back(
                std::make_shared<Friendly>(Friendly(position, callback, moving_entities.size())));
            break;
        default:
            throw std::invalid_argument("Illegal entity type");
    }
    return moving_entities.size() - 1;
}

void Field::build_tower(EntityType type) {
    if (this->team_status == Team::TeamEnemy) {
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
    this->team_status = Team::TeamFriendly;
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
        this->team_status = Team::TeamNeutral;
    }
}

std::shared_ptr<Stable> Field::get_tower() const { return this->tower; }

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

std::vector<std::shared_ptr<Unstable>> Field::get_moving_entities_const() const {
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
