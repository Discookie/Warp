#include "Special.h"

Special::Special(std::pair<int, int> position, CallbackClass gameModelCallback) {
    this->position = position;
    this->callback = gameModelCallback;
    this->isUpgraded = true;
    this->hp = 1000;
}

void Special::update() {

}

void Special::die() {

}

void Special::attack() {

}

int Special::removeValue() {
    return 0;
}

void Special::takeDamage(int amount) {
    this->hp -= amount;
    if(hp < 0){
        this->die();
    }
}
