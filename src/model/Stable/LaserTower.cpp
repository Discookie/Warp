#include "LaserTower.h"

LaserTower::LaserTower(
    Coordinate position, const std::shared_ptr<FieldEntityCallbackClass> &game_model_callback) {
    this->position = position;
    this->callback = game_model_callback;
    this->upgraded = false;
    this->hp       = 1000;
}

void LaserTower::update() {}

void LaserTower::die() { callback->die(shared_from_this()); }

void LaserTower::attack() { callback->attack(shared_from_this()); }

int LaserTower::remove_value() {
    if (upgraded) {
        return 100;
    }
    return 50;
}

void LaserTower::take_damage(int amount) {
    this->hp -= amount;
    if (hp < 0) {
        this->die();
    }
}
