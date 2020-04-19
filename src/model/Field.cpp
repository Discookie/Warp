#include "Field.h"

#include "Stable/Factory.h"
#include "model/Stable/LaserTower.h"
#include "Stable/HqAttack.h"
#include "Stable/HqDefense.h"
#include "Stable/Special.h"
#include "model/Stable/TeslaCoil.h"
#include "Stable/SniperTower.h"

Field::Field(Coordinate position, const std::shared_ptr<FieldEntityCallbackClass> &game_model_callback) {
    this->position = position;
    this->callback = game_model_callback;
    this->team_status = Team::Neutral;
    this->tower = nullptr;
    this->moving_entities = std::vector<std::shared_ptr<Unstable>>();
}

void Field::build_tower(EntityType type) {
    if (this->team_status == Team::Enemy) return;
    switch (type) {
        case EntityType::TypeFactory :
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

void Field::upgrade_tower(){
    this->tower->upgrade();
}

void Field::remove_tower() {
    this->tower = nullptr;
    if(this->moving_entities.empty()){
        this->team_status = Team::Neutral;
    }
}

std::shared_ptr<Stable> Field::get_tower() {
    return this->tower;
}


void Field::remove_entity_at(int ind) {
    this->moving_entities.erase(this->moving_entities.begin() + ind);
}

std::vector<std::shared_ptr<Unstable>> Field::get_moving_entities() {
    return this->moving_entities;
}

void Field::update_entities() {
    if(this->tower) {
        this->tower->update();
    }
    for (auto &me : this->moving_entities) {
        me->update();
    }
}

