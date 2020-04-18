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

std::vector<FieldEntity>&& TeslaCoil::collect_atteced_entities(
    const std::vector<std::vector<Field>>& fields) {
    return std::move(std::vector<FieldEntity>());
}

int TeslaCoil::get_damage() {
    if (upgraded)
        return Constants::TESLACOIL_UPGRADE_COST;
    else
        return Constants::TESLACOIL_BASE_ATTACK;
};

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
