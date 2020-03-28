#include "TeslaCoil.h"

TeslaCoil::TeslaCoil(Coordinate position,
    const  std::shared_ptr<FieldEntityCallbackClass>& gameModelCallback) {
    this->position = position;
    this->callback = gameModelCallback;
    this->upgraded = false;
    this->hp = CONSTANTS::TESLACOIL_BASE_MAX_HP;
}

void TeslaCoil::update() {

}

void TeslaCoil::die() {
    callback->die(shared_from_this());
}

void TeslaCoil::attack() {
    callback->attack(shared_from_this());
}

int TeslaCoil::removeValue() {
    if(upgraded){
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
