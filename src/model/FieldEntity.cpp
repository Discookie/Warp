#include "FieldEntity.h"

#include <model/Stable/Factory.h>
#include <model/Stable/HqAttack.h>
#include <model/Stable/HqDefense.h>
#include <model/Stable/LaserTower.h>
#include <model/Stable/SniperTower.h>
#include <model/Stable/Special.h>
#include <model/Stable/TeslaCoil.h>

#include "Constants.h"

/// Factory
template <>
int FieldEntity::cost_of<Factory>() {
    return Constants::FACTORY_BASE_COST;
}

template <>
int FieldEntity::base_max_hp_of<Factory>() {
    return Constants::FACTORY_BASE_MAX_HP;
}

template <>
int FieldEntity::base_attack_of<Factory>() {
    return Constants::FACTORY_ATTACK;
}

/// HqAttack
template <>
int FieldEntity::cost_of<HqAttack>() {
    return Constants::HQATTACK_BASE_COST;
}

template <>
int FieldEntity::base_max_hp_of<HqAttack>() {
    return Constants::HQATTACK_BASE_MAX_HP;
}

template <>
int FieldEntity::base_attack_of<HqAttack>() {
    return Constants::HQATTACK_BASE_ATTACK;
}

/// HqDefense
template <>
int FieldEntity::cost_of<HqDefense>() {
    return Constants::HQDEFENSE_BASE_COST;
}

template <>
int FieldEntity::base_max_hp_of<HqDefense>() {
    return Constants::HQDEFENSE_BASE_MAX_HP;
}

template <>
int FieldEntity::base_attack_of<HqDefense>() {
    return Constants::HQDEFENSE_BASE_ATTACK;
}

/// Special
template <>
int FieldEntity::cost_of<Special>() {
    return Constants::SPECIAL_BASE_COST;
}

template <>
int FieldEntity::base_max_hp_of<Special>() {
    return Constants::SPECIAL_BASE_MAX_HP;
}

template <>
int FieldEntity::base_attack_of<Special>() {
    return Constants::SPECIAL_BASE_ATTACK;
}

/// LaserTower
template <>
int FieldEntity::cost_of<LaserTower>() {
    return Constants::LASERTOWER_BASE_COST;
}

template <>
int FieldEntity::base_max_hp_of<LaserTower>() {
    return Constants::LASERTOWER_BASE_MAX_HP;
}

template <>
int FieldEntity::base_attack_of<LaserTower>() {
    return Constants::LASERTOWER_BASE_ATTACK;
}

/// TeslaCoil
template <>
int FieldEntity::cost_of<TeslaCoil>() {
    return Constants::TESLACOIL_BASE_COST;
}

template <>
int FieldEntity::base_max_hp_of<TeslaCoil>() {
    return Constants::TESLACOIL_BASE_MAX_HP;
}

template <>
int FieldEntity::base_attack_of<TeslaCoil>() {
    return Constants::TESLACOIL_BASE_ATTACK;
}

/// SniperTower
template <>
int FieldEntity::cost_of<SniperTower>() {
    return Constants::SNIPERTOWER_BASE_COST;
}

template <>
int FieldEntity::base_max_hp_of<SniperTower>() {
    return Constants::SNIPERTOWER_BASE_MAX_HP;
}

template <>
int FieldEntity::base_attack_of<SniperTower>() {
    return Constants::SNIPERTOWER_BASE_ATTACK;
}
