#include "Field.h"

#include "Stable/Factory.h"
#include "Stable/Stable1.h"
#include "Stable/HqAttack.h"
#include "Stable/HqDefense.h"
#include "Stable/Special.h"

Field::Field(std::pair<int, int> position){
    this->position = position;
    this->teamStatus = Team::Neutral;
    this->tower = std::nullopt;
    this->movingEntities = std::vector<std::shared_ptr<Unstable>>();
}

void Field::buildTower(EntityType type) {
    if (this->teamStatus == Team::Enemy) return;
    switch (type) {
        case EntityType::typeFactory :
            this->tower = std::dynamic_pointer_cast<Stable>(std::make_shared<Factory>(this->position));
            break;
        case EntityType::typeStable_1:
            this->tower = std::dynamic_pointer_cast<Stable>(std::make_shared<Stable1>(this->position));
            break;
        case EntityType::typeStable_2:
            this->tower = std::dynamic_pointer_cast<Stable>(std::make_shared<Stable1>(this->position));
            break;
        case EntityType::typeStable_3:
            this->tower = std::dynamic_pointer_cast<Stable>(std::make_shared<Stable1>(this->position));
            break;
        case EntityType::typeHqAttack:
            this->tower = std::dynamic_pointer_cast<Stable>(std::make_shared<HqAttack>(this->position));
            break;
        case EntityType::typeHqDefense:
            this->tower = std::dynamic_pointer_cast<Stable>(std::make_shared<HqDefense>(this->position));
            break;
        case EntityType::typeSpecial:
            this->tower = std::dynamic_pointer_cast<Stable>(std::make_shared<Special>(this->position));
            break;
        default:
            return;
    }
    this->teamStatus = Team::Friendly;
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

void Field::removeTower() {
    this->tower = std::nullopt;
    if(this->movingEntities.empty()){
        this->teamStatus = Team::Neutral;
    }

}

std::vector<std::shared_ptr<Unstable>> Field::getMovingEntities() {
    return this->movingEntities;
}
