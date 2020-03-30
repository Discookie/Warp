#include "HqAttack.h"

HqAttack::HqAttack(
    Coordinate position, const std::shared_ptr<FieldEntityCallbackClass> &game_model_callback) {
    this->position = position;
    this->callback = game_model_callback;
    this->upgraded = true;
    this->hp       = Constants::HQATTACK_BASE_MAX_HP;
}

void HqAttack::update() {}

void HqAttack::die() { callback->die(shared_from_this()); }

void HqAttack::attack() { callback->attack(shared_from_this()); }

int HqAttack::remove_value() {
    if (upgraded) {
        return 100;
    }
    return 50;
}

void HqAttack::take_damage(int amount) {
    this->hp -= amount;
    if (hp < 0) {
        this->die();
    }
}
