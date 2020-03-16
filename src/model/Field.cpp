#include "Field.h"

Field::Field(std::pair<int, int> position){
    this->position = position;
    this->teamStatus = Team::Neutral;
    this->tower = std::nullopt;
    this->movingEntities = std::vector<std::unique_ptr<Unstable>>();
}

void Field::buildTower(EntityType type) {
    switch (type) {
        case EntityType::typeFactory :
            this->tower = std::shared_ptr<Stable>(new Factory(this->position));
            return;
        case EntityType::typeStable_1:
            this->tower = std::shared_ptr<Stable>(new Stable1(this->position));
            return;
        case EntityType::typeStable_2:
            this->tower = std::shared_ptr<Stable>(new Stable1(this->position));
            return;
        case EntityType::typeStable_3:
            this->tower = std::shared_ptr<Stable>(new Stable1(this->position));
            return;
        case EntityType::typeHqAttack:
            this->tower = std::shared_ptr<Stable>(new HqAttack(this->position));
            return;
        case EntityType::typeHqDefense:
            this->tower = std::shared_ptr<Stable>(new HqDefense(this->position));
            return;
        case EntityType::typeSpecial:
            this->tower = std::shared_ptr<Stable>(new Special(this->position));
            return;
        default:
            return;
    }
}

void Field::updateEntities() {
    if(this->tower.has_value()){
        this->tower.value()->update();
    }
    for(auto& me : this->movingEntities){
        me->update();
    }
}

std::optional<std::shared_ptr<Stable>> Field::getTower() {
    if(this->tower.has_value()){
        return this->tower;
    }
    return std::nullopt;
}

std::vector<std::unique_ptr<Unstable>> Field::getMovingEntities() {
    return this->movingEntities;
}
