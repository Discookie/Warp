#include "HqDefense.h"
#include <memory>

HqDefense::HqDefense(std::pair<int, int> position, const std::shared_ptr<CallbackClass>& gameModelCallback) {
    this->position = position;
    this->callback = gameModelCallback;
    this->isUpgraded = true;
    this->hp = 1000;
}

HqDefense::HqDefense(HqDefense *pHqDefense) {
    this->position = pHqDefense->position;
    this->callback = pHqDefense->callback;
    this->isUpgraded = pHqDefense->isUpgraded;
    this->hp = pHqDefense->hp;
}

void HqDefense::update() {

}

void HqDefense::die() {
    callback->die(std::make_shared<HqDefense>(this));
}

void HqDefense::attack() {}

int HqDefense::removeValue() {
    if(isUpgraded){
        return 100;
    }
    return 50;
}

void HqDefense::takeDamage(int amount) {
    this->hp -= amount;
    if(hp < 0){
        this->die();
    }
}
