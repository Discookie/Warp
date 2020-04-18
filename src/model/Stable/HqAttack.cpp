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

std::vector<FieldEntity>&& HqAttack::collect_atteced_entities(
    const std::vector<std::vector<Field>>& fields) {
    return std::move(std::vector<FieldEntity>());
}

int HqAttack::get_damage() {
    return Constants::HQATTACK_BASE_ATTACK;
};

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
