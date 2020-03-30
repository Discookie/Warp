#ifndef WARP_CONSTANTS_H
#define WARP_CONSTANTS_H

namespace Constants {
// Stable
/// Factory
static const int FACTORY_BASE_COST                = 100;
static const int FACTORY_UPGRADE_COST             = 100;
static const int FACTORY_BASE_MAX_HP              = 1000;
static const int FACTORY_UPGRADE_MAX_HP           = 1500;
static const int FACTORY_ATTACK                   = 0;
static const int FACTORY_ATTACK_SPEED             = 0;
static const int FACTORY_BASE_PRODUCTION          = 10;
static const int FACTORY_UPGRADE_PRODUCTION       = 20;
static const int FACTORY_BASE_PRODUCTION_SPEED    = 10;
static const int FACTORY_UPGRADE_PRODUCTION_SPEED = 5;
static const int FACTORY_BASE_REMOVE_VALUE        = 50;
static const int FACTORY_UPGRADE_REMOVE_VALUE     = 100;

/// LaserTower
static const int LASERTOWER_BASE_COST    = 100;
static const int LASERTOWER_UPGRADE_COST = 100;
static const int LASERTOWER_BASE_MAX_HP  = 1000;
static const int LASERTOWER_BASE_ATTACK  = 100;

/// TeslaCoil
static const int TESLACOIL_BASE_COST    = 100;
static const int TESLACOIL_UPGRADE_COST = 100;
static const int TESLACOIL_BASE_MAX_HP  = 1000;
static const int TESLACOIL_BASE_ATTACK  = 100;

/// SniperTower
static const int SNIPERTOWER_BASE_COST    = 100;
static const int SNIPERTOWER_UPGRADE_COST = 100;
static const int SNIPERTOWER_BASE_MAX_HP  = 1000;
static const int SNIPERTOWER_BASE_ATTACK  = 100;

/// HqAttack
static const int HQATTACK_BASE_COST    = 100;
static const int HQATTACK_UPGRADE_COST = 0;
static const int HQATTACK_BASE_MAX_HP  = 1000;
static const int HQATTACK_BASE_ATTACK  = 100;

/// HqDefense
static const int HQDEFENSE_BASE_COST    = 100;
static const int HQDEFENSE_UPGRADE_COST = 0;
static const int HQDEFENSE_BASE_MAX_HP  = 1000;
static const int HQDEFENSE_BASE_ATTACK  = 100;

/// Special
static const int SPECIAL_BASE_COST    = 100;
static const int SPECIAL_UPGRADE_COST = 0;
static const int SPECIAL_BASE_MAX_HP  = 1000;
static const int SPECIAL_BASE_ATTACK  = 100;

// Unstable

}  // namespace Constants
#endif  // WARP_CONSTANTS_H
