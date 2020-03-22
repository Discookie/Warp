#include "SniperTower.h"

SniperTower::SniperTower(std::pair<int, int> position, CallbackClass gameModelCallback) {
    this->position = position;
    this->callback = gameModelCallback;
    this->isUpgraded = false;
    this->hp = CONSTANTS::SNIPERTOWER_BASE_MAX_HP;
}

void SniperTower::update() {

}

void SniperTower::die() {

}

void SniperTower::attack() {

}

int SniperTower::removeValue() {
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
