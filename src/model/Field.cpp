#include "Field.h"

#include "Stable/Factory.h"
#include "model/Stable/LaserTower.h"
#include "Stable/HqAttack.h"
#include "Stable/HqDefense.h"
#include "Stable/Special.h"
#include "model/Stable/TeslaCoil.h"
#include "Stable/SniperTower.h"

Field::Field(Coordinate position, const std::shared_ptr<FieldEntityCallbackClass> &gameModelCallback) {
    this->position = position;
    this->callback = gameModelCallback;
    this->teamStatus = Team::Neutral;
    this->tower = nullptr;
    this->movingEntities = std::vector<std::shared_ptr<Unstable>>();
}

void Field::buildTower(EntityType type) {
    if (this->teamStatus == Team::Enemy) return;
    switch (type) {
        case EntityType::typeFactory :
            this->tower = std::make_shared<Factory>(this->position, this->callback);
            break;
        case EntityType::typeLaserTower:
            this->tower = std::make_shared<LaserTower>(this->position, this->callback);
            break;
        case EntityType::typeTeslaCoil:
            this->tower = std::make_shared<TeslaCoil>(this->position, this->callback);
            break;
        case EntityType::typeSniperTower:
            this->tower = std::make_shared<SniperTower>(this->position, this->callback);
            break;
        case EntityType::typeHqAttack:
            this->tower = std::make_shared<HqAttack>(this->position, this->callback);
            break;
        case EntityType::typeHqDefense:
            this->tower = std::make_shared<HqDefense>(this->position, this->callback);
            break;
        case EntityType::typeSpecial:
            this->tower = std::make_shared<Special>(this->position, this->callback);
            break;
        default:
            return;
    }
    this->teamStatus = Team::Friendly;
}

void Field::upgradeTower(){
    this->tower->upgrade();
}

void Field::removeTower() {
    this->tower = nullptr;
    if(this->movingEntities.empty()){
        this->teamStatus = Team::Neutral;
    }
}

std::shared_ptr<Stable> Field::getTower() {
    return this->tower;
}


void Field::removeEntityAt(int ind) {
    this->movingEntities.erase(this->movingEntities.begin() + ind);
}

std::vector<std::shared_ptr<Unstable>> Field::getMovingEntities() {
    return this->movingEntities;
}

void Field::updateEntities() {
    if(this->tower) {
        this->tower->update();
    }
    for (auto &me : this->movingEntities) {
        me->update();
    }
}

