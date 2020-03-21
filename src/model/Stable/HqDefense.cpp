#include "HqDefense.h"

HqDefense::HqDefense(std::pair<int, int> position, CallbackClass gameModelCallback) {
    this->position = position;
    this->callback = gameModelCallback;
    this->isUpgraded = true;
    this->hp = 1000;
}

void HqDefense::update() {

}

void HqDefense::die() {

}

void HqDefense::attack() {

}

int HqDefense::removeValue() {
    if(isUpgraded){
        return 100;
    }
    return 50;
}

void HqDefense::takeDamage(int amount) {
    this->hp -= amount;
    if(hp < 0){
        this->die();
    }
}
