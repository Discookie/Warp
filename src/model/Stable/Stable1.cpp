#include "Stable1.h"

Stable1::Stable1(std::pair<int, int> position) {

}

void Stable1::update() {

}

void Stable1::upgrade() {
    this->isUpgraded = true;
}

void Stable1::die() {

}

void Stable1::attack() {

}

int Stable1::value() {
    if(isUpgraded){
        return 100;
    }
    return 50;
}

void Stable1::takeDamage(int amount) {
    this->hp -= amount;
    if(hp < 0){
        this->die();
    }
}
