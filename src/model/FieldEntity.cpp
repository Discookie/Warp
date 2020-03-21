#include "FieldEntity.h"

#include <model/Stable/Factory.h>
#include <model/Stable/HqAttack.h>
#include <model/Stable/HqDefense.h>
#include <model/Stable/Special.h>
#include <model/Stable/Stable1.h>

/// Factory
template<>
int FieldEntity::cost_of<Factory>() {
    return 100;
}
template<>
int FieldEntity::baseMaxHp_of<Factory>() {
    return 1000;
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

/// HqDefense
template<>
int FieldEntity::cost_of<HqDefense>() {
    return 100;
}
template<>
int FieldEntity::baseMaxHp_of<HqDefense>() {
    return 1000;
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

/// Stable1
template<>
int FieldEntity::cost_of<Stable1>() {
    return 100;
}
template<>
int FieldEntity::baseMaxHp_of<Stable1>() {
    return 1000;
}