#include "Factory.h"

Factory::Factory(std::pair<int, int> position, const std::shared_ptr<FieldEntityCallbackClass>& gameModelCallback) {
    this->position = position;
    this->callback = gameModelCallback;
    this->upgraded = false;
    this->hp = CONSTANTS::FACTORY_BASE_MAX_HP;
}

void Factory::produce() {
    callback->produce(shared_from_this());
}

void Factory::update() {

}

void Factory::die() {
    callback->die(shared_from_this());
}

void Factory::takeDamage(int amount) {
    this->hp -= amount;
    if(hp < 0){
        this->die();
    }
}

