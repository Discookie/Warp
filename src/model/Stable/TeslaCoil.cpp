#include "TeslaCoil.h"

TeslaCoil::TeslaCoil(std::pair<int, int> position, const  std::shared_ptr<CallbackClass>& gameModelCallback) {
    this->position = position;
    this->callback = gameModelCallback;
    this->isUpgraded = false;
    this->hp = CONSTANTS::TESLACOIL_BASE_MAX_HP;
}

TeslaCoil::TeslaCoil(TeslaCoil *pTeslaCoil) {
    this->position = pTeslaCoil->position;
    this->callback = pTeslaCoil->callback;
    this->isUpgraded = pTeslaCoil->isUpgraded;
    this->hp = pTeslaCoil->hp;
}

void TeslaCoil::update() {

}

void TeslaCoil::die() {
    callback->die(std::make_shared<TeslaCoil>(this));
}

void TeslaCoil::attack() {
    callback->attack(std::make_shared<TeslaCoil>(this));
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
