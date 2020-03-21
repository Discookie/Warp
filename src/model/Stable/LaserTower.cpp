#include "LaserTower.h"

LaserTower::LaserTower(std::pair<int, int> position, CallbackClass gameModelCallback) {
    this->position = position;
    this->callback = gameModelCallback;
    this->isUpgraded = false;
    this->hp = 1000;
}

void LaserTower::update() {

}

void LaserTower::die() {

}

void LaserTower::attack() {

}

int LaserTower::removeValue() {
    if(isUpgraded){
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
