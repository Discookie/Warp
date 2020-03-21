#include "FieldEntity.h"

#include <model/Stable/Factory.h>
#include <model/Stable/HqAttack.h>
#include <model/Stable/HqDefense.h>
#include <model/Stable/Special.h>
#include <model/Stable/LaserTower.h>
#include <model/Stable/TeslaCoil.h>
#include <model/Stable/SniperTower.h>

/// Factory
template<>
int FieldEntity::cost_of<Factory>() {
    return 100;
}
template<>
int FieldEntity::baseMaxHp_of<Factory>() {
    return 1000;
}
template<>
int FieldEntity::baseAttack_of<Factory>() {
    return 100;
}

/// HqAttack
template<>
int FieldEntity::cost_of<HqAttack>() {
    return 100;
}
template<>
int FieldEntity::baseMaxHp_of<HqAttack>() {
    return 0;
}
template<>
int FieldEntity::baseAttack_of<HqAttack>() {
    return 100;
}

/// HqDefense
template<>
int FieldEntity::cost_of<HqDefense>() {
    return 100;
}
template<>
int FieldEntity::baseMaxHp_of<HqDefense>() {
    return 1000;
}
template<>
int FieldEntity::baseAttack_of<HqDefense>() {
    return 0;
}

/// Special
template<>
int FieldEntity::cost_of<Special>() {
    return 100;
}
template<>
int FieldEntity::baseMaxHp_of<Special>() {
    return 1410065407;
}
template<>
int FieldEntity::baseAttack_of<Special>() {
    return 100;
}

/// LaserTower
template<>
int FieldEntity::cost_of<LaserTower>() {
    return 100;
}
template<>
int FieldEntity::baseMaxHp_of<LaserTower>() {
    return 1000;
}
template<>
int FieldEntity::baseAttack_of<LaserTower>() {
    return 100;
}

/// TeslaCoil
template<>
int FieldEntity::cost_of<TeslaCoil>() {
    return 100;
}
template<>
int FieldEntity::baseMaxHp_of<TeslaCoil>() {
    return 1000;
}
template<>
int FieldEntity::baseAttack_of<TeslaCoil>() {
    return 100;
}

/// SniperTower
template<>
int FieldEntity::cost_of<SniperTower>() {
    return 100;
}
template<>
int FieldEntity::baseMaxHp_of<SniperTower>() {
    return 1000;
}
template<>
int FieldEntity::baseAttack_of<SniperTower>() {
    return 100;
}
