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

std::vector<FieldEntity>&& SniperTower::collect_atteced_entities(
    const std::vector<std::vector<Field>>& fields) {
    return std::move(std::vector<FieldEntity>());
}

int SniperTower::get_damage() {
    if (upgraded)
        return Constants::SNIPERTOWER_UPGRADE_COST;
    else
        return Constants::SNIPERTOWER_BASE_ATTACK;
};

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
