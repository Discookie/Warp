#include "FieldEntity.h"

#include <model/Stable/Factory.h>
#include <model/Stable/HqAttack.h>
#include <model/Stable/HqDefense.h>
#include <model/Stable/Special.h>
#include <model/Stable/LaserTower.h>
#include <model/Stable/TeslaCoil.h>
#include <model/Stable/SniperTower.h>

#include "Constants.h"
/// Factory
template<>
int FieldEntity::cost_of<Factory>() {
    return CONSTANTS::FACTORY_BASE_COST;
}
template<>
int FieldEntity::baseMaxHp_of<Factory>() {
    return CONSTANTS::FACTORY_BASE_MAX_HP;
}
template<>
int FieldEntity::baseAttack_of<Factory>() {
    return CONSTANTS::FACTORY_ATTACK;
}

/// HqAttack
template<>
int FieldEntity::cost_of<HqAttack>() {
    return CONSTANTS::HQATTACK_BASE_COST;
}
template<>
int FieldEntity::baseMaxHp_of<HqAttack>() {
    return CONSTANTS::HQATTACK_BASE_MAX_HP;
}
template<>
int FieldEntity::baseAttack_of<HqAttack>() {
    return CONSTANTS::HQATTACK_BASE_ATTACK;
}

/// HqDefense
template<>
int FieldEntity::cost_of<HqDefense>() {
    return CONSTANTS::HQDEFENSE_BASE_COST;
}
template<>
int FieldEntity::baseMaxHp_of<HqDefense>() {
    return CONSTANTS::HQDEFENSE_BASE_MAX_HP;
}
template<>
int FieldEntity::baseAttack_of<HqDefense>() {
    return CONSTANTS::HQDEFENSE_BASE_ATTACK;
}

/// Special
template<>
int FieldEntity::cost_of<Special>() {
    return CONSTANTS::SPECIAL_BASE_COST;
}
template<>
int FieldEntity::baseMaxHp_of<Special>() {
    return CONSTANTS::SPECIAL_BASE_MAX_HP;
}
template<>
int FieldEntity::baseAttack_of<Special>() {
    return CONSTANTS::SPECIAL_BASE_ATTACK;
}

/// LaserTower
template<>
int FieldEntity::cost_of<LaserTower>() {
    return CONSTANTS::LASERTOWER_BASE_COST;
}
template<>
int FieldEntity::baseMaxHp_of<LaserTower>() {
    return CONSTANTS::LASERTOWER_BASE_MAX_HP;
}
template<>
int FieldEntity::baseAttack_of<LaserTower>() {
    return CONSTANTS::LASERTOWER_BASE_ATTACK;
}

/// TeslaCoil
template<>
int FieldEntity::cost_of<TeslaCoil>() {
    return CONSTANTS::TESLACOIL_BASE_COST;
}
template<>
int FieldEntity::baseMaxHp_of<TeslaCoil>() {
    return CONSTANTS::TESLACOIL_BASE_MAX_HP;
}
template<>
int FieldEntity::baseAttack_of<TeslaCoil>() {
    return CONSTANTS::TESLACOIL_BASE_ATTACK;
}

/// SniperTower
template<>
int FieldEntity::cost_of<SniperTower>() {
    return CONSTANTS::SNIPERTOWER_BASE_COST;
}
template<>
int FieldEntity::baseMaxHp_of<SniperTower>() {
    return CONSTANTS::SNIPERTOWER_BASE_MAX_HP;
}
template<>
int FieldEntity::baseAttack_of<SniperTower>() {
    return CONSTANTS::SNIPERTOWER_BASE_ATTACK;
}
