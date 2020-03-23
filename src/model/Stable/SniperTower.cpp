#include "SniperTower.h"

SniperTower::SniperTower(std::pair<int, int> position, const std::shared_ptr<CallbackClass>& gameModelCallback) {
    this->position = position;
    this->callback = gameModelCallback;
    this->isUpgraded = false;
    this->hp = CONSTANTS::SNIPERTOWER_BASE_MAX_HP;
}

SniperTower::SniperTower(SniperTower *pSniperTower) {
    this->position = pSniperTower->position;
    this->callback = pSniperTower->callback;
    this->isUpgraded = pSniperTower->isUpgraded;
    this->hp = pSniperTower->hp;
}

void SniperTower::update() {

}

void SniperTower::die() {
    callback->die(std::make_shared<SniperTower>(this));
}

void SniperTower::attack() {
    callback->attack(std::make_shared<SniperTower>(this));
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
