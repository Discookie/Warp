#include "Factory.h"

Factory::Factory(std::pair<int, int> position, CallbackClass gameModelCallback) {
    this->position = position;
    this->callback = gameModelCallback;
    this->isUpgraded = false;
    this->hp = 1000;
}

void Factory::update() {

}

void Factory::die() {

}

void Factory::attack() {
    callback.attack();
}

int Factory::removeValue() {
    if(isUpgraded){
        return 100;
    }
    return 50;
}

void Factory::takeDamage(int amount) {
    this->hp -= amount;
    if(hp < 0){
        this->die();
    }
}

