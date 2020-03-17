#include "HqAttack.h"

HqAttack::HqAttack(std::pair<int, int> position) {

}

void HqAttack::update() {

}

void HqAttack::upgrade() {
    this->isUpgraded = true;
}

void HqAttack::die() {

}

void HqAttack::attack() {

}

int HqAttack::value() {
    if(isUpgraded){
        return 100;
    }
    return 50;
}

void HqAttack::takeDamage(int amount) {
    this->hp -= amount;
    if(hp < 0){
        this->die();
    }
}
