#include "TeslaCoil.h"

TeslaCoil::TeslaCoil(
    Coordinate position, const std::shared_ptr<FieldEntityCallbackClass> &game_model_callback) {
    this->position = position;
    this->callback = game_model_callback;
    this->upgraded = false;
    this->hp       = Constants::TESLACOIL_BASE_MAX_HP;
}

void TeslaCoil::update() {}

void TeslaCoil::die() { callback->die(shared_from_this()); }

void TeslaCoil::attack() { callback->attack(shared_from_this()); }

int TeslaCoil::remove_value() {
    if (upgraded) {
        return 100;
    }
    return 50;
}

void TeslaCoil::take_damage(int amount) {
    this->hp -= amount;
    if (hp < 0) {
        this->die();
    }
}
