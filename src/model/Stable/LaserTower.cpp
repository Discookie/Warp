#include "LaserTower.h"

LaserTower::LaserTower(std::pair<int, int> position, const  std::shared_ptr<FieldEntityCallbackClass>& gameModelCallback) {
    this->position = position;
    this->callback = gameModelCallback;
    this->upgraded = false;
    this->hp = 1000;
}


void LaserTower::update() {

}

void LaserTower::die() {
    callback->die(shared_from_this());
}

void LaserTower::attack() {
    callback->attack(shared_from_this());
}

int LaserTower::removeValue() {
    if(upgraded){
        return 100;
    }
    return 50;
}

void LaserTower::takeDamage(int amount) {
    this->hp -= amount;
    if(hp < 0){
        this->die();
    }
}
