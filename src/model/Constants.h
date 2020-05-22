#ifndef WARP_CONSTANTS_H
#define WARP_CONSTANTS_H

#define MAKE_CONSTANT_DIFF(name, value) inline int name () { return value; }

namespace Constants {
/// Difficulty constants
    extern float diff;
//1s -> 30t
// Game
    static const int STARTING_GOLD = 200;
    static const int GOLD_GEN_AMOUNT = 50;
    static const int GOLD_GEN_SPEED = 90; // 3s
    static const int WAVE_COUNTDOWN_TIME = 1800;
    static const int WAVE_SPAWN_TIME_START = 0;
    static const int WAVE_SPAWN_TIME_END = -1800;
    static const int WAVE_OVER_TIME = -900;

    MAKE_CONSTANT_DIFF(FINAL_WAVE_NUMBER, 5 * diff);

/// Points
    static const int POINTS_FOR_TOWER_BUILD = 10;
    static const int POINTS_FOR_TOWER_UPGRADE = 5;
    static const int POINTS_FOR_TOWER_REMOVE = 10;

// Stable
/// Factory
    MAKE_CONSTANT_DIFF(FACTORY_BASE_COST, 100 * diff);

    MAKE_CONSTANT_DIFF(FACTORY_UPGRADE_COST, 1000 * diff);
    static const int FACTORY_MAX_HP = 1000;
    static const int FACTORY_DAMAGE = 0;
    static const int FACTORY_ATTACK_SPEED = 0;
    static const int FACTORY_BASE_PRODUCTION = 50;
    static const int FACTORY_UPGRADE_PRODUCTION = 100;
    static const int FACTORY_BASE_PRODUCTION_SPEED = 900;
    static const int FACTORY_UPGRADE_PRODUCTION_SPEED = 750;
    static const int FACTORY_BASE_REMOVE_VALUE = 50;
    static const int FACTORY_UPGRADE_REMOVE_VALUE = 500;

/// LaserTower
    MAKE_CONSTANT_DIFF(LASERTOWER_BASE_COST, 100 * diff);

    MAKE_CONSTANT_DIFF(LASERTOWER_UPGRADE_COST, 200 * diff);
    static const int LASERTOWER_MAX_HP = 1200;

    MAKE_CONSTANT_DIFF(LASERTOWER_BASE_DAMAGE, 100 * (2 - diff));

    MAKE_CONSTANT_DIFF(LASERTOWER_UPGRADE_DAMAGE, 200 * (2 - diff));
    static const int LASERTOWER_BASE_ATTACKSPEED = 120;
    static const int LASERTOWER_UPGRADE_ATTACKSPEED = 60;
    static const int LASERTOWER_BASE_REMOVE_VALUE = 50;
    static const int LASERTOWER_UPGRADE_REMOVE_VALUE = 100;

/// TeslaCoil
    MAKE_CONSTANT_DIFF(TESLACOIL_BASE_COST, 500 * diff);

    MAKE_CONSTANT_DIFF(TESLACOIL_UPGRADE_COST, 1000 * diff);
    static const int TESLACOIL_MAX_HP = 3000;

    MAKE_CONSTANT_DIFF(TESLACOIL_BASE_DAMAGE, 100 * (2 - diff));

    MAKE_CONSTANT_DIFF(TESLACOIL_UPGRADE_DAMAGE, 200 * (2 - diff));
    static const int TESLACOIL_BASE_ATTACKSPEED = 10;
    static const int TESLACOIL_ATTACK_RANGE = 1;
    static const int TESLACOIL_UPGRADE_ATTACKSPEED = 15;
    static const int TESLACOIL_BASE_REMOVE_VALUE = 50;
    static const int TESLACOIL_UPGRADE_REMOVE_VALUE = 100;

/// SniperTower
    MAKE_CONSTANT_DIFF(SNIPERTOWER_BASE_COST, 2500 * diff);

    MAKE_CONSTANT_DIFF(SNIPERTOWER_UPGRADE_COST, 2500 * diff);
    static const int SNIPERTOWER_MAX_HP = 100;

    MAKE_CONSTANT_DIFF(SNIPERTOWER_BASE_DAMAGE, 200 * (2 - diff));

    MAKE_CONSTANT_DIFF(SNIPERTOWER_UPGRADE_DAMAGE, 300 * (2 - diff));
    static const int SNIPERTOWER_BASE_ATTACKSPEED = 450;
    static const int SNIPERTOWER_UPGRADE_ATTACKSPEED = 300;
    static const int SNIPERTOWER_BASE_REMOVE_VALUE = 1500;
    static const int SNIPERTOWER_UPGRADE_REMOVE_VALUE = 3000;

/// HqAttack
    MAKE_CONSTANT_DIFF(HQATTACK_BASE_COST, 1000 * diff);
    static const int HQATTACK_UPGRADE_COST = 0;
    static const int HQATTACK_MAX_HP = 2000;

    MAKE_CONSTANT_DIFF(HQATTACK_DAMAGE, 300 * (2 - diff));
    static const int HQATTACK_ATTACKSPEED = 90;
    static const int HQATTACK_REMOVE_VALUE = 1000;

/// HqDefense
    MAKE_CONSTANT_DIFF(HQDEFENSE_BASE_COST, 1000 * diff);
    static const int HQDEFENSE_UPGRADE_COST = 0;
    static const int HQDEFENSE_MAX_HP = 10000;
    static const int HQDEFENSE_DAMAGE = 0;
    static const int HQDEFENSE_ATTACKSPEED = 0;
    static const int HQDEFENSE_REMOVE_VALUE = 500;

/// Special
    MAKE_CONSTANT_DIFF(SPECIAL_BASE_COST, 500 * diff);
    static const int SPECIAL_UPGRADE_COST = 0;
    static const int SPECIAL_MAX_HP = 0;

    MAKE_CONSTANT_DIFF(SPECIAL_DAMAGE, 1000 * (2 - diff));
    static const int SPECIAL_ATTACKSPEED = 90;
    static const int SPECIAL_ATTACK_RANGE = 5;
    static const int SPECIAL_REMOVE_VALUE = 0;

// Unstable
/// Friendly
    MAKE_CONSTANT_DIFF(FRIENDLY_COST, 200 * diff);
    static const int FRIENDLY_MAX_HP = 500;

    MAKE_CONSTANT_DIFF(FRIENDLY_DAMAGE, 200 * (2 - diff));
    static const int FRIENDLY_ATTACKSPEED = 90;
    static const int FRIENDLY_MOVESPEED = 60;

/// Enemy
    static const int ENEMY_COST = 0;

/// Alien
    MAKE_CONSTANT_DIFF(ALIEN_MAX_HP, 100 * diff);
    static const int ALIEN_DAMAGE = 300;
    static const int ALIEN_ATTACKSPEED = 60;

    MAKE_CONSTANT_DIFF(ALIEN_MOVESPEED, 100 * (2 - diff));
    static const int ALIEN_SPWN_BASE_FREQUENCY = 200;
    static const int ALIEN_SPWN_WAVE_FREQUENCY = 100;

/// Octopus
    MAKE_CONSTANT_DIFF(OCTOPUS_MAX_HP, 1500 * diff);
    static const int OCTOPUS_DAMAGE = 100;
    static const int OCTOPUS_ATTACKSPEED = 120;

    MAKE_CONSTANT_DIFF(OCTOPUS_MOVESPEED, 120 * (2 - diff));
    static const int OCTOPUS_SPWN_BASE_FREQUENCY = 1000;
    static const int OCTOPUS_SPWN_WAVE_FREQUENCY = 250;

/// Robot
    MAKE_CONSTANT_DIFF(ROBOT_MAX_HP, 2500 * diff);
    static const int ROBOT_DAMAGE = 600;
    static const int ROBOT_ATTACKSPEED = 120;

    MAKE_CONSTANT_DIFF(ROBOT_MOVESPEED, 150 * (2 - diff));
    static const int ROBOT_SPWN_BASE_FREQUENCY = 5000;
    static const int ROBOT_SPWN_WAVE_FREQUENCY = 2500;

};  // namespace Constants

#undef MAKE_CONSTANT_DIFF

#endif  // WARP_CONSTANTS_H