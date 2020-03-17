#include "Factory.h"

Factory::Factory(std::pair<int, int> position) {
    this->position = position;
    this->isUpgraded = false;
    this->hp = 1000;
}

void Factory::update() {

}

void Factory::upgrade() {
    this->isUpgraded = true;
}

void Factory::die() {

}

void Factory::attack() {

}

int Factory::value() {
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

