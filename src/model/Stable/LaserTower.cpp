#include "LaserTower.h"

LaserTower::LaserTower(std::pair<int, int> position, const  std::shared_ptr<CallbackClass>& gameModelCallback) {
    this->position = position;
    this->callback = gameModelCallback;
    this->isUpgraded = false;
    this->hp = 1000;
}

LaserTower::LaserTower(LaserTower *pLaserTower) {
    this->position = pLaserTower->position;
    this->callback = pLaserTower->callback;
    this->isUpgraded = pLaserTower->isUpgraded;
    this->hp = pLaserTower->hp;
}

void LaserTower::update() {

}

void LaserTower::die() {
    callback->die(std::make_shared<LaserTower>(this));
}

void LaserTower::attack() {
    callback->attack(std::make_shared<LaserTower>(this));
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
