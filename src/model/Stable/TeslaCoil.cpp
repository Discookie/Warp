#include "TeslaCoil.h"

TeslaCoil::TeslaCoil(std::pair<int, int> position, CallbackClass gameModelCallback) {
    this->position = position;
    this->callback = gameModelCallback;
    this->isUpgraded = false;
    this->hp = CONSTANTS::TESLACOIL_BASE_MAX_HP;
}

void TeslaCoil::update() {

}

void TeslaCoil::die() {

}

void TeslaCoil::attack() {

}

int TeslaCoil::removeValue() {
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
