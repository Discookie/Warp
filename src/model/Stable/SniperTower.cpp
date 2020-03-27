#include "SniperTower.h"

SniperTower::SniperTower(std::pair<int, int> position, const std::shared_ptr<FieldEntityCallbackClass>& gameModelCallback) {
    this->position = position;
    this->callback = gameModelCallback;
    this->upgraded = false;
    this->hp = CONSTANTS::SNIPERTOWER_BASE_MAX_HP;
}

void SniperTower::update() {

}

void SniperTower::die() {
    callback->die(shared_from_this());
}

void SniperTower::attack() {
    callback->attack(shared_from_this());
}

int SniperTower::removeValue() {
    if(upgraded){
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
