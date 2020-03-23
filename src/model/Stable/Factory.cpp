#include "Factory.h"

Factory::Factory(std::pair<int, int> position, const std::shared_ptr<CallbackClass>& gameModelCallback) {
    this->position = position;
    this->callback = gameModelCallback;
    this->isUpgraded = false;
    this->hp = CONSTANTS::FACTORY_BASE_MAX_HP;
}

Factory::Factory(Factory *pFactory) {
    this->position = pFactory->position;
    this->callback = pFactory->callback;
    this->isUpgraded = pFactory->isUpgraded;
    this->hp = pFactory->hp;
}

void Factory::produce() {
    callback->produce(std::make_shared<Factory>(this));
}

void Factory::update() {

}

void Factory::die() {
    callback->die(std::make_shared<Factory>(this));
}

void Factory::takeDamage(int amount) {
    this->hp -= amount;
    if(hp < 0){
        this->die();
    }
}

