#include "HqDefense.h"

#include <memory>

HqDefense::HqDefense(
    Coordinate position, const std::shared_ptr<FieldEntityCallbackClass> &game_model_callback) {
    this->position = position;
    this->callback = game_model_callback;
    this->upgraded = true;
    this->hp       = 1000;
}

void HqDefense::update() {}

void HqDefense::die() { callback->die(shared_from_this()); }

int HqDefense::remove_value() {
    if (upgraded) {
        return 100;
    }
    return 50;
}

void HqDefense::take_damage(int amount) {
    this->hp -= amount;
    if (hp < 0) {
        this->die();
    }
}
