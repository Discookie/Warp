#include "Special.h"

Special::Special(std::pair<int, int> position, const std::shared_ptr<CallbackClass>& gameModelCallback) {
    this->position = position;
    this->callback = gameModelCallback;
    this->isUpgraded = true;
    this->hp = CONSTANTS::SPECIAL_BASE_MAX_HP;
}

Special::Special(Special *pSpecial) {
    this->position = pSpecial->position;
    this->callback = pSpecial->callback;
    this->isUpgraded = pSpecial->isUpgraded;
    this->hp = pSpecial->hp;
}

void Special::update() {

}

void Special::die() {
    callback->die(std::make_shared<Special>(this));
}

void Special::attack() {
    callback->attack(std::make_shared<Special>(this));
    this->die();
}

