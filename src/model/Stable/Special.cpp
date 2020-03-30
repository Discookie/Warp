#include "Special.h"

Special::Special(
    Coordinate position, const std::shared_ptr<FieldEntityCallbackClass> &game_model_callback) {
    this->position = position;
    this->callback = game_model_callback;
    this->upgraded = true;
    this->hp       = Constants::SPECIAL_BASE_MAX_HP;
}

void Special::update() {}

void Special::die() { callback->die(shared_from_this()); }

void Special::attack() {
    callback->attack(shared_from_this());
    this->die();
}
