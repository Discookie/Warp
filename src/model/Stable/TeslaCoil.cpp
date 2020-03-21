#include "TeslaCoil.h"

TeslaCoil::TeslaCoil(std::pair<int, int> position) {

}

void TeslaCoil::update() {

}

void TeslaCoil::upgrade() {
    this->isUpgraded = true;
}

void TeslaCoil::die() {

}

void TeslaCoil::attack() {

}

int TeslaCoil::value() {
    if(isUpgraded){
        return 100;
    }
    return 50;
}

void TeslaCoil::takeDamage(int amount) {
    this->hp -= amount;
    if(hp < 0){
        this->die();
    }
}
