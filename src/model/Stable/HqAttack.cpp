#include "HqAttack.h"

HqAttack::HqAttack(std::pair<int, int> position, const std::shared_ptr<FieldEntityCallbackClass>& gameModelCallback) {
    this->position = position;
    this->callback = gameModelCallback;
    this->upgraded = true;
    this->hp = CONSTANTS::HQATTACK_BASE_MAX_HP;
}

void HqAttack::update() {

}

void HqAttack::die() {
    callback->die(shared_from_this());
}

void HqAttack::attack() {
    callback->attack(shared_from_this());
}

int HqAttack::removeValue() {
    if(upgraded){
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
