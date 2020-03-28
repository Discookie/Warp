#include "HqDefense.h"
#include <memory>

HqDefense::HqDefense(Coordinate position,
    const std::shared_ptr<FieldEntityCallbackClass>& gameModelCallback) {
    this->position = position;
    this->callback = gameModelCallback;
    this->upgraded = true;
    this->hp = 1000;
}

void HqDefense::update() {

}

void HqDefense::die() {
    callback->die(shared_from_this());
}

int HqDefense::removeValue() {
    if(upgraded){
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
