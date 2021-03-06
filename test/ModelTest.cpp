//
// Created by Boldizsár Poór (boldar99@gmail.com) on 2020. 03. 22..
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <gtest/gtest.h>
#include <model/Constants.h>
#include <model/Field.h>
#include <model/FieldEntityCallback.h>
#include <model/GameModel.h>
#include <model/Stable/Factory.h>
#include <model/Stable/HqAttack.h>
#include <model/Stable/HqDefense.h>
#include <model/Stable/LaserTower.h>
#include <model/Stable/SniperTower.h>
#include <model/Stable/Special.h>
#include <model/Stable/TeslaCoil.h>
#include <model/Team.h>
#include <model/Unstable/Alien.h>
#include <model/Unstable/Friendly.h>
#include <model/Unstable/Octopus.h>
#include <model/Unstable/Robot.h>

#include <functional>
#include <sstream>

class MockCallback : public FieldEntityCallback {
public:
    int pro_calls;
    int mov_calls;
    int att_calls;
    int die_calls;

    MockCallback()
        : pro_calls(0),
          mov_calls(0),
          att_calls(0),
          die_calls(0),
          FieldEntityCallback(
              [this](const std::shared_ptr<FieldEntity> &obj) { ++pro_calls; },
              [this](const std::shared_ptr<FieldEntity> &obj) { ++mov_calls; },
              [this](const std::shared_ptr<FieldEntity> &obj) { ++att_calls; },
              [this](const std::shared_ptr<FieldEntity> &obj) { ++die_calls; }) {}
};
/*
class TFactory : public Factory {
public:
    TFactory(Coordinate c, const std::shared_ptr<FieldEntityCallback> &fe_cb) : Factory(c, fe_cb) {}
    void p_die() { die(); }
    void p_produce() { produce(); }
};
*/
/*
TEST(TestMockCallback, Test) {
    std::shared_ptr<MockCallback> cb = std::make_shared<MockCallback>();
    std::shared_ptr<Factory> factory = std::make_shared<Factory>(Factory({1, 0}, cb));
    std::shared_ptr<Alien> alien     = std::make_shared<Alien>(Alien({1, 0}, cb, 0));
    EXPECT_EQ(cb->pro_calls, 0);
    EXPECT_EQ(cb->mov_calls, 0);
    EXPECT_EQ(cb->att_calls, 0);
    EXPECT_EQ(cb->die_calls, 0);
    factory->produce();
    EXPECT_EQ(cb->pro_calls, 1);
    factory->die();
    EXPECT_EQ(cb->die_calls, 1);
    alien->attack();
    EXPECT_EQ(cb->att_calls, 1);
    alien->move();
    EXPECT_EQ(cb->mov_calls, 1);
}
*/
TEST(CoordinateTest, eqTest) {
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 10; ++j) {
            Coordinate c1 = {i, j};
            for (int ii = 0; ii < 12; ++ii) {
                for (int jj = 0; jj < 10; ++jj) {
                    Coordinate c2 = {ii, jj};
                    if (ii == i && jj == j) {
                        EXPECT_EQ(c1, c2);
                    } else {
                        EXPECT_NE(c1, c2);
                    }
                }
            }
        }
    }
}

TEST(CoordinateTest, ioTest) {
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 10; ++j) {
            std::stringstream s;
            Coordinate c1 = {i, j};
            Coordinate c2 = {1, 0};
            s << c1;
            s >> c2;
            EXPECT_EQ(c1, c2);
        }
    }
}

class FieldFixture : public ::testing::Test {
protected:
    std::shared_ptr<MockCallback> cb;
    Field field;
    FieldFixture() : cb(new MockCallback), field({1, 0}, cb) {}
};

TEST_F(FieldFixture, InitTest) {
    EXPECT_FALSE(field.get_tower_const());
    EXPECT_EQ(field.get_team_status(), Team::TeamNeutral);
    EXPECT_TRUE(field.get_moving_entities().empty());
}

// TEST_F(FieldFixture, BuildTest) {
//     field.add_friendly_entity(EntityType::TypeFactory);
//
//     EXPECT_EQ(field.get_team_status(), Team::TeamFriendly);
//     ASSERT_TRUE(field.get_tower());
//
//     EXPECT_ANY_THROW(field.add_friendly_entity(EntityType::TypeFactory))
//         << "Double build should throw exception";
//     field.get_tower()->die();
//     EXPECT_EQ(field.get_team_status(), Team::TeamNeutral);
// }
//
// TEST_F(FieldFixture, BuildFactoryTest) {
//     field.add_friendly_entity(EntityType::TypeFactory);
//     EXPECT_EQ(field.get_tower()->get_entity_type(), EntityType::TypeFactory);
//
//     std::dynamic_pointer_cast<Factory>(field.get_tower())->produce();
//     EXPECT_EQ(cb->pro_calls, 1);
//     field.get_tower()->die();
//     EXPECT_EQ(cb->die_calls, 1);
// }
//
// TEST_F(FieldFixture, BuildLaserTowerTest) {
//     field.add_friendly_entity(EntityType::TypeLaserTower);
//     EXPECT_EQ(field.get_tower()->get_entity_type(), EntityType::TypeLaserTower);
//
//     field.get_tower()->attack();
//     EXPECT_EQ(cb->att_calls, 1);
//     field.get_tower()->die();
//     EXPECT_EQ(cb->die_calls, 1);
// }
//
// TEST_F(FieldFixture, BuildTeslaCoilTest) {
//     field.add_friendly_entity(EntityType::TypeTeslaCoil);
//     EXPECT_EQ(field.get_tower()->get_entity_type(), EntityType::TypeTeslaCoil);
//
//     field.get_tower()->attack();
//     EXPECT_EQ(cb->att_calls, 1);
//     field.get_tower()->die();
//     EXPECT_EQ(cb->die_calls, 1);
// }
//
// TEST_F(FieldFixture, BuildSniperTowerTest) {
//     field.add_friendly_entity(EntityType::TypeSniperTower);
//     EXPECT_EQ(field.get_tower()->get_entity_type(), EntityType::TypeSniperTower);
//
//     field.get_tower()->attack();
//     EXPECT_EQ(cb->att_calls, 1);
//     field.get_tower()->die();
//     EXPECT_EQ(cb->die_calls, 1);
// }
//
// TEST_F(FieldFixture, BuildSpecialTest) {
//     field.add_friendly_entity(EntityType::TypeSpecial);
//     EXPECT_EQ(field.get_tower()->get_entity_type(), EntityType::TypeSpecial);
//
//     field.get_tower()->attack();
//     EXPECT_EQ(cb->att_calls, 1);
//     field.get_tower()->die();
//     EXPECT_EQ(cb->die_calls, 1);
// }

TEST_F(FieldFixture, RemoveTowerTest) {
    EXPECT_ANY_THROW(field.remove_tower()) << "Removing nothing should throw exception";

    field.build_tower(EntityType::TypeFactory);
    field.remove_tower();

    EXPECT_FALSE(field.get_tower_const());
    EXPECT_EQ(field.get_team_status(), Team::TeamNeutral);
    EXPECT_TRUE(field.get_moving_entities().empty());
}

TEST_F(FieldFixture, UpgradeTest) {
    EXPECT_ANY_THROW(field.upgrade_tower()) << "Updating nothing should throw exception";

    field.build_tower(EntityType::TypeFactory);

    EXPECT_FALSE(field.get_tower_const()->is_upgraded());

    field.upgrade_tower();

    EXPECT_TRUE(field.get_tower_const()->is_upgraded());
    EXPECT_EQ(field.get_team_status(), Team::TeamFriendly);
    EXPECT_TRUE(field.get_moving_entities().empty());

    EXPECT_ANY_THROW(field.upgrade_tower()) << "Double upgrade should throw exception";
}

TEST_F(FieldFixture, UpdateTest) {
    field.build_tower(EntityType::TypeFactory);
    for (int i = 0; i < Constants::FACTORY_BASE_PRODUCTION; ++i) {
        EXPECT_EQ(cb->pro_calls, 0);
        field.update_entities();
    }
    field.add_moving_entity(std::make_shared<Friendly>(Friendly({1, 0}, cb, 0)));
    for (int i = 0; i < Constants::FRIENDLY_MOVESPEED; ++i) {
        EXPECT_EQ(cb->mov_calls, 0);
        field.update_entities();
    }
    EXPECT_EQ(cb->mov_calls, 1);
}

TEST_F(FieldFixture, AddEntityTest) {
    EXPECT_EQ(field.get_moving_entities().size(), 0);
    field.add_moving_entity(std::make_shared<Alien>(Alien({1, 0}, cb, 0)));
    EXPECT_EQ(field.get_moving_entities().size(), 1);
    field.add_moving_entity(std::make_shared<Octopus>(Octopus({1, 0}, cb, 0)));
    EXPECT_EQ(field.get_moving_entities().size(), 2);
    field.add_moving_entity(std::make_shared<Robot>(Robot({1, 0}, cb, 0)));
    EXPECT_EQ(field.get_moving_entities().size(), 3);
    EXPECT_EQ(field.get_team_status(), Team::TeamEnemy);
    EXPECT_ANY_THROW(field.add_moving_entity(std::make_shared<Friendly>(Friendly({1, 0}, cb, 0))));
    EXPECT_ANY_THROW(field.build_tower(EntityType::TypeTeslaCoil));
}

TEST_F(FieldFixture, AddFriendlyTest) {
    field.add_moving_entity(std::make_shared<Friendly>(Friendly({1, 0}, cb, 0)));
    EXPECT_EQ(field.get_team_status(), Team::TeamFriendly);
    EXPECT_ANY_THROW(field.add_moving_entity(std::make_shared<Robot>(Robot({1, 0}, cb, 0))));
    EXPECT_NO_THROW(field.build_tower(EntityType::TypeTeslaCoil));
}

TEST_F(FieldFixture, RemoveEntityTest) {
    field.add_moving_entity(std::make_shared<Alien>(Alien({1, 0}, cb, 0)));
    field.add_moving_entity(std::make_shared<Octopus>(Octopus({1, 0}, cb, 0)));
    field.add_moving_entity(std::make_shared<Robot>(Robot({1, 0}, cb, 0)));
    field.remove_entity_at(0);
    EXPECT_EQ(field.get_moving_entities().size(), 2);
    EXPECT_EQ(field.get_team_status(), Team::TeamEnemy);
    field.remove_entity_at(0);
    EXPECT_EQ(field.get_moving_entities().size(), 1);
    EXPECT_EQ(field.get_team_status(), Team::TeamEnemy);
    field.remove_entity_at(0);
    EXPECT_EQ(field.get_moving_entities().size(), 0);
    EXPECT_EQ(field.get_team_status(), Team::TeamNeutral);
}

TEST_F(FieldFixture, EqTest) {
    Field field1({1, 1}, cb);
    EXPECT_NE(field, field1);  // coord
    Field field2({1, 0}, cb);
    field2.build_tower(EntityType::TypeSniperTower);
    EXPECT_NE(field, field2);  // tower
    Field field3({1, 0}, cb);
    field3.add_moving_entity(std::make_shared<Friendly>(Friendly({1, 0}, cb, 0)));
    EXPECT_NE(field, field3);  // moving_entity && teamstatus
    Field field4({1, 0}, cb);
    field4.add_moving_entity(std::make_shared<Alien>(Alien({1, 0}, cb, 0)));
    EXPECT_NE(field, field3);  // moving_entity && teamstatus
    Field field5({1, 0}, cb);
    EXPECT_EQ(field, field5);
}

TEST_F(FieldFixture, IOTest) {
    std::stringstream ss;
    Field field1({1, 0}, cb);

    field.add_moving_entity(std::make_shared<Friendly>(Friendly({1, 0}, cb, 0)));
    field.add_moving_entity(std::make_shared<Friendly>(Friendly({1, 0}, cb, 1)));
    field.add_moving_entity(std::make_shared<Friendly>(Friendly({1, 0}, cb, 2)));
    field.build_tower(EntityType::TypeSniperTower);
    field.upgrade_tower();

    ASSERT_NE(field, field1);
    ss << field;
    ss >> field1;
    EXPECT_EQ(field, field1);
}

class FactoryFixture : public ::testing::Test {
protected:
    std::shared_ptr<MockCallback> cb;
    std::shared_ptr<Factory> factory;
    FactoryFixture() : cb(new MockCallback()), factory(new Factory({1, 0}, cb)) {}
};

TEST_F(FactoryFixture, InitTest) {
    EXPECT_EQ(factory->attack_speed(), Constants::FACTORY_ATTACK_SPEED);
    EXPECT_EQ(factory->production_speed(), Constants::FACTORY_BASE_PRODUCTION_SPEED);
    EXPECT_EQ(factory->cost(), Constants::FACTORY_BASE_COST());
    EXPECT_EQ(factory->upgrade_cost(), Constants::FACTORY_UPGRADE_COST());
    EXPECT_EQ(factory->max_hp(), Constants::FACTORY_MAX_HP);
    EXPECT_EQ(factory->production_amount(), Constants::FACTORY_BASE_PRODUCTION);
    EXPECT_EQ(factory->remove_value(), Constants::FACTORY_BASE_REMOVE_VALUE);
    EXPECT_EQ(factory->get_position(), ((Coordinate) {1, 0}));
    EXPECT_EQ(factory->get_vector_pos(), -1);
    EXPECT_FALSE(factory->is_upgraded());
    EXPECT_TRUE(factory->is_friendly());
}

TEST_F(FactoryFixture, UpgradeTest) {
    factory->upgrade();
    EXPECT_EQ(factory->attack_speed(), Constants::FACTORY_ATTACK_SPEED);
    EXPECT_EQ(factory->production_speed(), Constants::FACTORY_UPGRADE_PRODUCTION_SPEED);
    EXPECT_EQ(factory->cost(), Constants::FACTORY_BASE_COST());
    EXPECT_EQ(factory->upgrade_cost(), Constants::FACTORY_UPGRADE_COST());
    EXPECT_EQ(factory->max_hp(), Constants::FACTORY_MAX_HP);
    EXPECT_EQ(factory->production_amount(), Constants::FACTORY_UPGRADE_PRODUCTION);
    EXPECT_EQ(factory->remove_value(), Constants::FACTORY_UPGRADE_REMOVE_VALUE);
    EXPECT_EQ(factory->get_position(), ((Coordinate) {1, 0}));
    EXPECT_EQ(factory->get_vector_pos(), -1);
    EXPECT_TRUE(factory->is_upgraded());
    EXPECT_TRUE(factory->is_friendly());
}

TEST_F(FactoryFixture, DieTest) {
    factory->take_damage(Constants::FACTORY_MAX_HP);
    EXPECT_EQ(cb->die_calls, 1);
}

TEST_F(FactoryFixture, BaseProduceTest) {
    for (int i = 0; i < Constants::FACTORY_BASE_PRODUCTION_SPEED; ++i) {
        EXPECT_EQ(cb->pro_calls, 0);
        factory->update();
    }
    EXPECT_EQ(cb->pro_calls, 1);
}

TEST_F(FactoryFixture, UpgradeProduceTest) {
    factory->upgrade();
    for (int i = 0; i < Constants::FACTORY_UPGRADE_PRODUCTION_SPEED; ++i) {
        EXPECT_EQ(cb->pro_calls, 0);
        factory->update();
    }
    EXPECT_EQ(cb->pro_calls, 1);
}

class LaserTowerFixture : public ::testing::Test {
protected:
    std::shared_ptr<MockCallback> cb;
    std::shared_ptr<LaserTower> laserTower;
    LaserTowerFixture() : cb(new MockCallback()), laserTower(new LaserTower({1, 0}, cb)) {}
};

TEST_F(LaserTowerFixture, InitTest) {
    EXPECT_EQ(laserTower->attack_speed(), Constants::LASERTOWER_BASE_ATTACKSPEED);
    EXPECT_EQ(laserTower->damage(), Constants::LASERTOWER_BASE_DAMAGE());
    EXPECT_EQ(laserTower->cost(), Constants::LASERTOWER_BASE_COST());
    EXPECT_EQ(laserTower->remove_value(), Constants::LASERTOWER_BASE_REMOVE_VALUE);
    EXPECT_EQ(laserTower->upgrade_cost(), Constants::LASERTOWER_UPGRADE_COST());
    EXPECT_EQ(laserTower->max_hp(), Constants::LASERTOWER_MAX_HP);
    EXPECT_EQ(laserTower->get_position(), ((Coordinate) {1, 0}));
    EXPECT_EQ(laserTower->get_vector_pos(), -1);
    EXPECT_FALSE(laserTower->is_upgraded());
    EXPECT_TRUE(laserTower->is_friendly());
}

TEST_F(LaserTowerFixture, UpgradeTest) {
    laserTower->upgrade();
    EXPECT_EQ(laserTower->attack_speed(), Constants::LASERTOWER_UPGRADE_ATTACKSPEED);
    EXPECT_EQ(laserTower->cost(), Constants::LASERTOWER_BASE_COST());
    EXPECT_EQ(laserTower->upgrade_cost(), Constants::LASERTOWER_UPGRADE_COST());
    EXPECT_EQ(laserTower->max_hp(), Constants::LASERTOWER_MAX_HP);
    EXPECT_EQ(laserTower->remove_value(), Constants::LASERTOWER_UPGRADE_REMOVE_VALUE);
    EXPECT_EQ(laserTower->get_position(), ((Coordinate) {1, 0}));
    EXPECT_EQ(laserTower->get_vector_pos(), -1);
    EXPECT_TRUE(laserTower->is_upgraded());
    EXPECT_TRUE(laserTower->is_friendly());
}

TEST_F(LaserTowerFixture, DieTest) {
    laserTower->take_damage(Constants::LASERTOWER_MAX_HP);
    EXPECT_EQ(cb->die_calls, 1);
}

TEST_F(LaserTowerFixture, BaseProduceTest) {
    for (int i = 0; i < Constants::LASERTOWER_BASE_ATTACKSPEED; ++i) {
        EXPECT_EQ(cb->att_calls, 0);
        laserTower->update();
    }
    EXPECT_EQ(cb->att_calls, 1);
}

TEST_F(LaserTowerFixture, UpgradeProduceTest) {
    laserTower->upgrade();
    for (int i = 0; i < Constants::LASERTOWER_UPGRADE_ATTACKSPEED; ++i) {
        EXPECT_EQ(cb->att_calls, 0);
        laserTower->update();
    }
    EXPECT_EQ(cb->att_calls, 1);
}

class SniperTowerFixture : public ::testing::Test {
protected:
    std::shared_ptr<MockCallback> cb;
    std::shared_ptr<SniperTower> sniperTower;
    SniperTowerFixture() : cb(new MockCallback()), sniperTower(new SniperTower({1, 0}, cb)) {}
};

TEST_F(SniperTowerFixture, InitTest) {
    EXPECT_EQ(sniperTower->attack_speed(), Constants::SNIPERTOWER_BASE_ATTACKSPEED);
    EXPECT_EQ(sniperTower->damage(), Constants::SNIPERTOWER_BASE_DAMAGE());
    EXPECT_EQ(sniperTower->cost(), Constants::SNIPERTOWER_BASE_COST());
    EXPECT_EQ(sniperTower->remove_value(), Constants::SNIPERTOWER_BASE_REMOVE_VALUE);
    EXPECT_EQ(sniperTower->upgrade_cost(), Constants::SNIPERTOWER_UPGRADE_COST());
    EXPECT_EQ(sniperTower->max_hp(), Constants::SNIPERTOWER_MAX_HP);
    EXPECT_EQ(sniperTower->get_position(), ((Coordinate) {1, 0}));
    EXPECT_EQ(sniperTower->get_vector_pos(), -1);
    EXPECT_FALSE(sniperTower->is_upgraded());
    EXPECT_TRUE(sniperTower->is_friendly());
}

TEST_F(SniperTowerFixture, UpgradeTest) {
    sniperTower->upgrade();
    EXPECT_EQ(sniperTower->attack_speed(), Constants::SNIPERTOWER_UPGRADE_ATTACKSPEED);
    EXPECT_EQ(sniperTower->cost(), Constants::SNIPERTOWER_BASE_COST());
    EXPECT_EQ(sniperTower->upgrade_cost(), Constants::SNIPERTOWER_UPGRADE_COST());
    EXPECT_EQ(sniperTower->max_hp(), Constants::SNIPERTOWER_MAX_HP);
    EXPECT_EQ(sniperTower->remove_value(), Constants::SNIPERTOWER_UPGRADE_REMOVE_VALUE);
    EXPECT_EQ(sniperTower->get_position(), ((Coordinate) {1, 0}));
    EXPECT_EQ(sniperTower->get_vector_pos(), -1);
    EXPECT_TRUE(sniperTower->is_upgraded());
    EXPECT_TRUE(sniperTower->is_friendly());
}

TEST_F(SniperTowerFixture, DieTest) {
    sniperTower->take_damage(Constants::SNIPERTOWER_MAX_HP);
    EXPECT_EQ(cb->die_calls, 1);
}

TEST_F(SniperTowerFixture, BaseProduceTest) {
    for (int i = 0; i < Constants::SNIPERTOWER_BASE_ATTACKSPEED; ++i) {
        EXPECT_EQ(cb->att_calls, 0);
        sniperTower->update();
    }
    EXPECT_EQ(cb->att_calls, 1);
}

TEST_F(SniperTowerFixture, UpgradeProduceTest) {
    sniperTower->upgrade();
    for (int i = 0; i < Constants::SNIPERTOWER_UPGRADE_ATTACKSPEED; ++i) {
        EXPECT_EQ(cb->att_calls, 0);
        sniperTower->update();
    }
    EXPECT_EQ(cb->att_calls, 1);
}

class TeslaCoilFixture : public ::testing::Test {
protected:
    std::shared_ptr<MockCallback> cb;
    std::shared_ptr<TeslaCoil> teslaCoil;
    TeslaCoilFixture() : cb(new MockCallback()), teslaCoil(new TeslaCoil({1, 0}, cb)) {}
};

TEST_F(TeslaCoilFixture, InitTest) {
    EXPECT_EQ(teslaCoil->attack_speed(), Constants::TESLACOIL_BASE_ATTACKSPEED);
    EXPECT_EQ(teslaCoil->damage(), Constants::TESLACOIL_BASE_DAMAGE());
    EXPECT_EQ(teslaCoil->cost(), Constants::TESLACOIL_BASE_COST());
    EXPECT_EQ(teslaCoil->remove_value(), Constants::TESLACOIL_BASE_REMOVE_VALUE);
    EXPECT_EQ(teslaCoil->upgrade_cost(), Constants::TESLACOIL_UPGRADE_COST());
    EXPECT_EQ(teslaCoil->max_hp(), Constants::TESLACOIL_MAX_HP);
    EXPECT_EQ(teslaCoil->get_position(), ((Coordinate) {1, 0}));
    EXPECT_EQ(teslaCoil->get_vector_pos(), -1);
    EXPECT_FALSE(teslaCoil->is_upgraded());
    EXPECT_TRUE(teslaCoil->is_friendly());
}

TEST_F(TeslaCoilFixture, UpgradeTest) {
    teslaCoil->upgrade();
    EXPECT_EQ(teslaCoil->attack_speed(), Constants::TESLACOIL_UPGRADE_ATTACKSPEED);
    EXPECT_EQ(teslaCoil->cost(), Constants::TESLACOIL_BASE_COST());
    EXPECT_EQ(teslaCoil->upgrade_cost(), Constants::TESLACOIL_UPGRADE_COST());
    EXPECT_EQ(teslaCoil->max_hp(), Constants::TESLACOIL_MAX_HP);
    EXPECT_EQ(teslaCoil->remove_value(), Constants::TESLACOIL_UPGRADE_REMOVE_VALUE);
    EXPECT_EQ(teslaCoil->get_position(), ((Coordinate) {1, 0}));
    EXPECT_EQ(teslaCoil->get_vector_pos(), -1);
    EXPECT_TRUE(teslaCoil->is_upgraded());
    EXPECT_TRUE(teslaCoil->is_friendly());
}

TEST_F(TeslaCoilFixture, DieTest) {
    teslaCoil->take_damage(Constants::TESLACOIL_MAX_HP);
    EXPECT_EQ(cb->die_calls, 1);
}

TEST_F(TeslaCoilFixture, BaseProduceTest) {
    for (int i = 0; i < Constants::TESLACOIL_BASE_ATTACKSPEED; ++i) {
        EXPECT_EQ(cb->att_calls, 0);
        teslaCoil->update();
    }
    EXPECT_EQ(cb->att_calls, 1);
}

TEST_F(TeslaCoilFixture, UpgradeProduceTest) {
    teslaCoil->upgrade();
    for (int i = 0; i < Constants::TESLACOIL_UPGRADE_ATTACKSPEED; ++i) {
        EXPECT_EQ(cb->att_calls, 0);
        teslaCoil->update();
    }
    EXPECT_EQ(cb->att_calls, 1);
}

class GameModelFixture : public ::testing::Test {
protected:
    GameModel game_model;
    GameModelFixture() : game_model() {}
};

TEST_F(GameModelFixture, InitTest) {
    EXPECT_EQ(game_model.get_points(), 0);
    EXPECT_EQ(game_model.get_wave_number(), 0);
    EXPECT_EQ(game_model.get_wave_progress(), Constants::WAVE_COUNTDOWN_TIME);
    EXPECT_EQ(game_model.get_gold(), Constants::STARTING_GOLD);
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 10; ++j) {
            EXPECT_FALSE(game_model.get_field_const({i, j}).get_tower_const());
            EXPECT_TRUE(game_model.get_field_const({i, j}).get_moving_entities_const().empty());
            EXPECT_EQ(game_model.get_field_const({i, j}).get_team_status(), Team::TeamNeutral);
        }
    }
}

TEST_F(GameModelFixture, EqTest) {
    GameModel game_model1 = {};
    EXPECT_EQ(game_model, game_model1);
    game_model1.update();
    EXPECT_NE(game_model, game_model1);
    game_model.update();
    EXPECT_EQ(game_model, game_model1);
}

TEST_F(GameModelFixture, IOTest) {
    std::stringstream ss;
    GameModel game_model1 = {};
    for (int i = 0; i < 100; ++i) {
        game_model.update();
    }
    ASSERT_NE(game_model, game_model1);
    ss << game_model;
    ss >> game_model1;
    EXPECT_EQ(game_model, game_model1);
}

TEST_F(GameModelFixture, SaveLoadTest) {
    std::stringstream ss;
    GameModel game_model1 = {};
    for (int i = 0; i < 5; ++i) {
        game_model.update();
        game_model1.update();
    }
    ASSERT_EQ(game_model, game_model1);
    game_model.save_game("test.txt");
    for (int i = 0; i < 5; ++i) {
        game_model1.update();
    }
    game_model1.load_game("test.txt");
    EXPECT_EQ(game_model, game_model1);
}

TEST_F(GameModelFixture, NewGameTest) {
    GameModel game_model1;
    for (int i = 0; i < 100; ++i) {
        game_model.update();
    }
    ASSERT_NE(game_model, game_model1);
    game_model.new_game();
    EXPECT_EQ(game_model, game_model1);
}

TEST_F(GameModelFixture, BuildTest1) {
    for (int i = 0; i < 12; ++i) {
        game_model.select_tower((EntityType)i);
        if (game_model.is_buildable((EntityType)i) || i == EntityType::TypeFriendly) {
            if (i == EntityType::TypeHqAttack || i == EntityType::TypeHqDefense) {
                EXPECT_EQ(game_model.add_friendly_entity({0, i}), std::nullopt);
            } else {
                EXPECT_EQ(game_model.add_friendly_entity({i, 0}), std::nullopt);
            }
        } else {
            EXPECT_NE(game_model.add_friendly_entity({i, 0}), std::nullopt);
        }
    }
}

TEST_F(GameModelFixture, BuildTest2) {
    game_model.select_tower(TypeFactory);
    while (!game_model.is_buildable(TypeFactory)) {
        game_model.update();
    }
    game_model.add_friendly_entity({1, 0});
    EXPECT_EQ(game_model.get_field_const({1, 0}).get_team_status(), Team::TeamFriendly);
    while (!game_model.is_buildable(TypeFactory)) {
        game_model.update();
    }
    EXPECT_NE(game_model.add_friendly_entity({1, 0}), std::nullopt);
}

#pragma clang diagnostic pop
