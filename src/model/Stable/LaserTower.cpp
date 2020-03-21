#include "LaserTower.h"

LaserTower::LaserTower(std::pair<int, int> position) {

}

void LaserTower::update() {

}

void LaserTower::upgrade() {
    this->isUpgraded = true;
}

void LaserTower::die() {

}

void LaserTower::attack() {

}

int LaserTower::value() {
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
