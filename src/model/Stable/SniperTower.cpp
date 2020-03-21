#include "SniperTower.h"

SniperTower::SniperTower(std::pair<int, int> position) {

}

void SniperTower::update() {

}

void SniperTower::upgrade() {
    this->isUpgraded = true;
}

void SniperTower::die() {

}

void SniperTower::attack() {

}

int SniperTower::value() {
    if(isUpgraded){
        return 100;
    }
    return 50;
}

void SniperTower::takeDamage(int amount) {
    this->hp -= amount;
    if(hp < 0){
        this->die();
    }
}
