#include "HqAttack.h"

HqAttack::HqAttack(std::pair<int, int> position, CallbackClass gameModelCallback) {
    this->position = position;
    this->callback = gameModelCallback;
    this->isUpgraded = true;
    this->hp = 1000;
}

void HqAttack::update() {

}

void HqAttack::die() {

}

void HqAttack::attack() {

}

int HqAttack::removeValue() {
    if(isUpgraded){
        return 100;
    }
    return 50;
}

void HqAttack::takeDamage(int amount) {
    this->hp -= amount;
    if(hp < 0){
        this->die();
    }
}
