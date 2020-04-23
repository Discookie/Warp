#ifndef WARP_CONSTANTS_H
#define WARP_CONSTANTS_H

#define MAKE_CONSTANT_DIFF(name, value) inline int name () { return value; }

namespace Constants {
/// Difficulty constants
    float diff;

// Game
    static const int STARTING_GOLD = 0;
    static const int GOLD_GEN_AMOUNT = 50;
    static const int GOLD_GEN_SPEED = 100;
    static const int WAVE_COUNTDOWN_TIME = 10000;
    static const int WAVE_SPAWN_TIME_START = 0;
    static const int WAVE_SPAWN_TIME_END = -500;
    static const int WAVE_OVER_TIME = -1000;
    static const int SPAWN_ENEMIES_TIME = 10;

    MAKE_CONSTANT_DIFF(FINAL_WAVE_NUMBER, 5 * diff);

/// Points
    static const int POINTS_FOR_TOWER_BUILD = 10;
    static const int POINTS_FOR_TOWER_UPGRADE = 5;
    static const int POINTS_FOR_TOWER_REMOVE = 10;

// Stable
/// Factory
    MAKE_CONSTANT_DIFF(FACTORY_BASE_COST, 100 * diff);

    MAKE_CONSTANT_DIFF(FACTORY_UPGRADE_COST, 200 * diff);
    static const int FACTORY_MAX_HP = 1000;
    static const int FACTORY_DAMAGE = 0;
    static const int FACTORY_ATTACK_SPEED = 0;
    static const int FACTORY_BASE_PRODUCTION = 10;
    static const int FACTORY_UPGRADE_PRODUCTION = 20;
    static const int FACTORY_BASE_PRODUCTION_SPEED = 10;
    static const int FACTORY_UPGRADE_PRODUCTION_SPEED = 5;
    static const int FACTORY_BASE_REMOVE_VALUE = 50;
    static const int FACTORY_UPGRADE_REMOVE_VALUE = 100;

/// LaserTower
    MAKE_CONSTANT_DIFF(LASERTOWER_BASE_COST, 100 * diff);

    MAKE_CONSTANT_DIFF(LASERTOWER_UPGRADE_COST, 200 * diff);
    static const int LASERTOWER_MAX_HP = 1000;

    MAKE_CONSTANT_DIFF(LASERTOWER_BASE_DAMAGE, 100 * (2 - diff));

    MAKE_CONSTANT_DIFF(LASERTOWER_UPGRADE_DAMAGE, 200 * (2 - diff));
    static const int LASERTOWER_BASE_ATTACKSPEED = 100;
    static const int LASERTOWER_UPGRADE_ATTACKSPEED = 100;
    static const int LASERTOWER_BASE_REMOVE_VALUE = 50;
    static const int LASERTOWER_UPGRADE_REMOVE_VALUE = 100;

/// TeslaCoil
    MAKE_CONSTANT_DIFF(TESLACOIL_BASE_COST, 100 * diff);

    MAKE_CONSTANT_DIFF(TESLACOIL_UPGRADE_COST, 200 * diff);
    static const int TESLACOIL_MAX_HP = 1000;

    MAKE_CONSTANT_DIFF(TESLACOIL_BASE_DAMAGE, 100 * (2 - diff));

    MAKE_CONSTANT_DIFF(TESLACOIL_UPGRADE_DAMAGE, 200 * (2 - diff));
    static const int TESLACOIL_BASE_ATTACKSPEED = 100;
    static const int TESLACOIL_ATTACK_RANGE = 1;
    static const int TESLACOIL_UPGRADE_ATTACKSPEED = 100;
    static const int TESLACOIL_BASE_REMOVE_VALUE = 50;
    static const int TESLACOIL_UPGRADE_REMOVE_VALUE = 100;

/// SniperTower
    MAKE_CONSTANT_DIFF(SNIPERTOWER_BASE_COST, 100 * diff);

    MAKE_CONSTANT_DIFF(SNIPERTOWER_UPGRADE_COST, 200 * diff);
    static const int SNIPERTOWER_MAX_HP = 1000;

    MAKE_CONSTANT_DIFF(SNIPERTOWER_BASE_DAMAGE, 1000 * (2 - diff));

    MAKE_CONSTANT_DIFF(SNIPERTOWER_UPGRADE_DAMAGE, 2000 * (2 - diff));
    static const int SNIPERTOWER_BASE_ATTACKSPEED = 100;
    static const int SNIPERTOWER_UPGRADE_ATTACKSPEED = 100;
    static const int SNIPERTOWER_BASE_REMOVE_VALUE = 50;
    static const int SNIPERTOWER_UPGRADE_REMOVE_VALUE = 100;

/// HqAttack
    MAKE_CONSTANT_DIFF(HQATTACK_BASE_COST, 100 * diff);
    static const int HQATTACK_UPGRADE_COST = 0;
    static const int HQATTACK_MAX_HP = 1000;

    MAKE_CONSTANT_DIFF(HQATTACK_DAMAGE, 100 * (2 - diff));
    static const int HQATTACK_ATTACKSPEED = 100;
    static const int HQATTACK_REMOVE_VALUE = 100;

/// HqDefense
    MAKE_CONSTANT_DIFF(HQDEFENSE_BASE_COST, 100 * diff);
    static const int HQDEFENSE_UPGRADE_COST = 0;
    static const int HQDEFENSE_MAX_HP = 10000;
    static const int HQDEFENSE_DAMAGE = 0;
    static const int HQDEFENSE_ATTACKSPEED = 100;
    static const int HQDEFENSE_REMOVE_VALUE = 100;

/// Special
    MAKE_CONSTANT_DIFF(SPECIAL_BASE_COST, 100 * diff);
    static const int SPECIAL_UPGRADE_COST = 0;
    static const int SPECIAL_MAX_HP = 0;

    MAKE_CONSTANT_DIFF(SPECIAL_DAMAGE, 100 * (2 - diff));
    static const int SPECIAL_ATTACKSPEED = 100;
    static const int SPECIAL_ATTACK_RANGE = 5;
    static const int SPECIAL_REMOVE_VALUE = 0;

// Unstable
/// Friendly
    MAKE_CONSTANT_DIFF(FRIENDLY_COST, 100 * diff);
    static const int FRIENDLY_MAX_HP = 1000;

    MAKE_CONSTANT_DIFF(FRIENDLY_DAMAGE, 100 * (2 - diff));
    static const int FRIENDLY_ATTACKSPEED = 100;
    static const int FRIENDLY_MOVESPEED = 100;

/// Enemy
    static const int ENEMY_COST = 0;

/// Alien
    MAKE_CONSTANT_DIFF(ALIEN_MAX_HP, 500 * diff);
    static const int ALIEN_DAMAGE = 100;
    static const int ALIEN_ATTACKSPEED = 100;

    MAKE_CONSTANT_DIFF(ALIEN_MOVESPEED, 50 * (2 - diff));
    static const int ALIEN_SPWN_BASE_FREQUENCY = 200;
    static const int ALIEN_SPWN_WAVE_FREQUENCY = 100;

/// Octopus
    MAKE_CONSTANT_DIFF(OCTOPUS_MAX_HP, 1500 * diff);
    static const int OCTOPUS_DAMAGE = 100;
    static const int OCTOPUS_ATTACKSPEED = 100;

    MAKE_CONSTANT_DIFF(OCTOPUS_MOVESPEED, 150 * (2 - diff));
    static const int OCTOPUS_SPWN_BASE_FREQUENCY = 600;
    static const int OCTOPUS_SPWN_WAVE_FREQUENCY = 300;

/// Robot
    MAKE_CONSTANT_DIFF(ROBOT_MAX_HP, 1000 * diff);
    static const int ROBOT_DAMAGE = 100;
    static const int ROBOT_ATTACKSPEED = 100;

    MAKE_CONSTANT_DIFF(ROBOT_MOVESPEED, 100 * (2 - diff));
    static const int ROBOT_SPWN_BASE_FREQUENCY = 1000;
    static const int ROBOT_SPWN_WAVE_FREQUENCY = 500;

};  // namespace Constants

#undef MAKE_CONSTANT_DIFF

#endif  // WARP_CONSTANTS_H