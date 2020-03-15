#include "Factory.h"

Factory::Factory(std::pair<int, int> position) {
    this->position = position;
    this->isUpgraded = false;
    this->production = 100;
    this->hp = 1000;
    this->maxHp = 1000;
}

void Factory::update() {

}

void Factory::upgrade() {

}

void Factory::die() {

}

void Factory::attack() {

}

int Factory::value() {

}

void Factory::takeDamage(int amount) {

}
