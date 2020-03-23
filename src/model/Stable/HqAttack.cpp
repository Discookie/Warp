#include "HqAttack.h"

HqAttack::HqAttack(std::pair<int, int> position, const std::shared_ptr<CallbackClass>& gameModelCallback) {
    this->position = position;
    this->callback = gameModelCallback;
    this->isUpgraded = true;
    this->hp = CONSTANTS::HQATTACK_BASE_MAX_HP;
}

HqAttack::HqAttack(HqAttack *pHqAttack) {
    this->position = pHqAttack->position;
    this->callback = pHqAttack->callback;
    this->isUpgraded = pHqAttack->isUpgraded;
    this->hp = pHqAttack->hp;
}

void HqAttack::update() {

}

void HqAttack::die() {
    callback->die(std::make_shared<HqAttack>(this));
}

void HqAttack::attack() {
    callback->attack(std::make_shared<HqAttack>(this));
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
