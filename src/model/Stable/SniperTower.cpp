#include "SniperTower.h"

SniperTower::SniperTower(
    Coordinate position, const std::shared_ptr<FieldEntityCallbackClass> &game_model_callback) {
    this->position = position;
    this->callback = game_model_callback;
    this->upgraded = false;
    this->hp       = Constants::SNIPERTOWER_BASE_MAX_HP;
}

void SniperTower::update() {}

void SniperTower::die() { callback->die(shared_from_this()); }

void SniperTower::attack() { callback->attack(shared_from_this()); }

int SniperTower::remove_value() {
    if (upgraded) {
        return 100;
    }
    return 50;
}

void SniperTower::take_damage(int amount) {
    this->hp -= amount;
    if (hp < 0) {
        this->die();
    }
}
