#include "Factory.h"

Factory::Factory(
    Coordinate position, const std::shared_ptr<FieldEntityCallbackClass> &game_model_callback) {
    this->position = position;
    this->callback = game_model_callback;
    this->upgraded = false;
    this->hp       = Constants::FACTORY_BASE_MAX_HP;
}

void Factory::produce() { callback->produce(shared_from_this()); }

void Factory::update() {}

void Factory::die() { callback->die(shared_from_this()); }

void Factory::take_damage(int amount) {
    this->hp -= amount;
    if (hp < 0) {
        this->die();
    }
}
