#include "HqDefense.h"

HqDefense::HqDefense(std::pair<int, int> position) {

}

void HqDefense::update() {

}

void HqDefense::upgrade() {
    this->isUpgraded = true;
}

void HqDefense::die() {

}

void HqDefense::attack() {

}

int HqDefense::value() {
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
