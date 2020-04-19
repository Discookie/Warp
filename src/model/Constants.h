#ifndef WARP_CONSTANTS_H
#define WARP_CONSTANTS_H

namespace Constants {
// Stable
/// Factory
    static const int FACTORY_BASE_COST                  = 100;
    static const int FACTORY_UPGRADE_COST               = 100;
    static const int FACTORY_MAX_HP                     = 1000;
    static const int FACTORY_DAMAGE                     = 0;
    static const int FACTORY_ATTACK_SPEED               = 0;
    static const int FACTORY_BASE_PRODUCTION            = 10;
    static const int FACTORY_UPGRADE_PRODUCTION         = 20;
    static const int FACTORY_BASE_PRODUCTION_SPEED      = 10;
    static const int FACTORY_UPGRADE_PRODUCTION_SPEED   = 5;
    static const int FACTORY_BASE_REMOVE_VALUE          = 50;
    static const int FACTORY_UPGRADE_REMOVE_VALUE       = 100;

/// LaserTower
    static const int LASERTOWER_BASE_COST    = 100;
    static const int LASERTOWER_UPGRADE_COST = 100;
    static const int LASERTOWER_MAX_HP  = 1000;
    static const int LASERTOWER_BASE_DAMAGE  = 100;
    static const int LASERTOWER_UPGRADE_DAMAGE  = 100;
    static const int LASERTOWER_BASE_ATTACKSPEED  = 100;
    static const int LASERTOWER_UPGRADE_ATTACKSPEED  = 100;
    static const int LASERTOWER_BASE_REMOVE_VALUE          = 50;
    static const int LASERTOWER_UPGRADE_REMOVE_VALUE       = 100;


    /// TeslaCoil
    static const int TESLACOIL_BASE_COST    = 100;
    static const int TESLACOIL_UPGRADE_COST = 100;
    static const int TESLACOIL_MAX_HP  = 1000;
    static const int TESLACOIL_BASE_DAMAGE  = 100;
    static const int TESLACOIL_UPGRADE_DAMAGE  = 100;
    static const int TESLACOIL_BASE_ATTACKSPEED  = 100;
    static const int TESLACOIL_UPGRADE_ATTACKSPEED  = 100;
    static const int TESLACOIL_BASE_REMOVE_VALUE          = 50;
    static const int TESLACOIL_UPGRADE_REMOVE_VALUE       = 100;

/// SniperTower
    static const int SNIPERTOWER_BASE_COST    = 100;
    static const int SNIPERTOWER_UPGRADE_COST = 100;
    static const int SNIPERTOWER_MAX_HP  = 1000;
    static const int SNIPERTOWER_BASE_DAMAGE  = 100;
    static const int SNIPERTOWER_UPGRADE_DAMAGE  = 100;
    static const int SNIPERTOWER_BASE_ATTACKSPEED  = 100;
    static const int SNIPERTOWER_UPGRADE_ATTACKSPEED  = 100;
    static const int SNIPERTOWER_BASE_REMOVE_VALUE          = 50;
    static const int SNIPERTOWER_UPGRADE_REMOVE_VALUE       = 100;

/// HqAttack
    static const int HQATTACK_BASE_COST    = 100;
    static const int HQATTACK_UPGRADE_COST = 0;
    static const int HQATTACK_MAX_HP  = 1000;
    static const int HQATTACK_DAMAGE  = 100;
    static const int HQATTACK_ATTACKSPEED  = 100;
    static const int HQATTACK_REMOVE_VALUE  = 100;

/// HqDefense
    static const int HQDEFENSE_BASE_COST    = 100;
    static const int HQDEFENSE_UPGRADE_COST = 0;
    static const int HQDEFENSE_MAX_HP  = 1000;
    static const int HQDEFENSE_DAMAGE  = 0;
    static const int HQDEFENSE_ATTACKSPEED  = 100;
    static const int HQDEFENSE_REMOVE_VALUE = 100;

/// Special
    static const int SPECIAL_BASE_COST    = 100;
    static const int SPECIAL_UPGRADE_COST = 0;
    static const int SPECIAL_MAX_HP  = 0;
    static const int SPECIAL_DAMAGE  = 100;
    static const int SPECIAL_ATTACKSPEED  = 100;
    static const int SPECIAL_REMOVE_VALUE = 0;

// Unstable
/// Friendly
    static const int FRIENDLY_COST    = 100;
    static const int FRIENDLY_MAX_HP  = 1000;
    static const int FRIENDLY_DAMAGE  = 100;
    static const int FRIENDLY_ATTACKSPEED  = 100;
    static const int FRIENDLY_MOVESPEED  = 100;

/// Enemy
    static const int ENEMY_COST = 0;

/// Alien
    static const int ALIEN_MAX_HP  = 1000;
    static const int ALIEN_DAMAGE  = 100;
    static const int ALIEN_ATTACKSPEED  = 100;
    static const int ALIEN_MOVESPEED  = 100;

/// Octopus
    static const int OCTOPUS_MAX_HP  = 1000;
    static const int OCTOPUS_DAMAGE  = 100;
    static const int OCTOPUS_ATTACKSPEED  = 100;
    static const int OCTOPUS_MOVESPEED  = 100;

/// Robot
    static const int ROBOT_MAX_HP  = 1000;
    static const int ROBOT_DAMAGE  = 100;
    static const int ROBOT_ATTACKSPEED  = 100;
    static const int ROBOT_MOVESPEED  = 100;

}
#endif //WARP_CONSTANTS_H
