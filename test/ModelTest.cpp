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

TEST(TestMockCallback, Test) {
    std::shared_ptr<MockCallback> cb = std::make_shared<MockCallback>();
    std::shared_ptr<Factory> factory = std::make_shared<Factory>(Factory({0, 0}, cb));
    std::shared_ptr<Alien> alien     = std::make_shared<Alien>(Alien({0, 0}, cb, 0));
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

TEST(CoordinateTest, eqTest) {
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 10; ++j) {
            Coordinate c1 = {i,j};
            for (int ii = 0; ii < 12; ++ii) {
                for (int jj = 0; jj < 10; ++jj) {
                    Coordinate c2 = {ii,jj};
                    if (ii == i && jj == j)
                        EXPECT_EQ(c1, c2);
                    else
                        EXPECT_NE(c1, c2);
                }
            }
        }
    }
}

TEST(CoordinateTest, ioTest) {
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 10; ++j) {
            std::stringstream s;
            Coordinate c1 = {i,j};
            Coordinate c2;
            s << c1;
            s >> c2;
            EXPECT_EQ(c1, c2);
        }
    }
}

class GameModelFixture : public ::testing::Test {
protected:
    //GameModel game_model;
    //GameModelFixture() : game_model() {}
};

TEST_F(GameModelFixture, InitTest) {
    GameModel game_model = {};
    EXPECT_EQ(game_model.get_points(), 0);
    EXPECT_EQ(game_model.get_wave_number(), 0);
    // EXPECT_EQ(game_model.get_wave_progress(), 0);
    EXPECT_EQ(game_model.get_gold(), 0);
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 12; ++j) {
            // EXPECT_FALSE(game_model.get_field({i, j}).get_tower());
            // EXPECT_TRUE(game_model.get_field({i, j}).get_moving_entities().empty());
            // EXPECT_EQ(game_model.get_field_const({i, j}).get_team_status(), Team::Neutral);
        }
    }
}

class FieldFixture : public ::testing::Test {
protected:
    std::shared_ptr<MockCallback> cb;
    Field field;
    FieldFixture() : cb(new MockCallback), field({0, 0}, cb) {}
};

TEST_F(FieldFixture, InitTest) {
    EXPECT_FALSE(field.get_tower());
    EXPECT_EQ(field.get_team_status(), Team::Neutral);
    EXPECT_TRUE(field.get_moving_entities().empty());
}

TEST_F(FieldFixture, BuildTest) {
    field.build_tower(EntityType::TypeFactory);

    EXPECT_EQ(field.get_team_status(), Team::Friendly);
    ASSERT_TRUE(field.get_tower());

    EXPECT_ANY_THROW(field.build_tower(EntityType::TypeFactory))
        << "Double build should throw exception";
}

TEST_F(FieldFixture, BuildFactoryTest) {
    field.build_tower(EntityType::TypeFactory);
    EXPECT_EQ(typeid(*field.get_tower()), typeid(Factory));

    auto a = std::dynamic_pointer_cast<Factory>(field.get_tower());
    a->produce();
    EXPECT_EQ(cb->pro_calls, 1);
    field.get_tower()->die();
    EXPECT_EQ(cb->die_calls, 1);
}

TEST_F(FieldFixture, BuildLaserTowerTest) {
    field.build_tower(EntityType::TypeLaserTower);
    EXPECT_EQ(typeid(*field.get_tower()), typeid(LaserTower));

    field.get_tower()->attack();
    EXPECT_EQ(cb->att_calls, 1);
    field.get_tower()->die();
    EXPECT_EQ(cb->die_calls, 1);
}

TEST_F(FieldFixture, BuildTeslaCoilTest) {
    field.build_tower(EntityType::TypeTeslaCoil);
    EXPECT_EQ(typeid(*field.get_tower()), typeid(TeslaCoil));

    field.get_tower()->attack();
    EXPECT_EQ(cb->att_calls, 1);
    field.get_tower()->die();
    EXPECT_EQ(cb->die_calls, 1);
}

TEST_F(FieldFixture, BuildSniperTowerTest) {
    field.build_tower(EntityType::TypeSniperTower);
    EXPECT_EQ(typeid(*field.get_tower()), typeid(SniperTower));

    field.get_tower()->attack();
    EXPECT_EQ(cb->att_calls, 1);
    field.get_tower()->die();
    EXPECT_EQ(cb->die_calls, 1);
}

TEST_F(FieldFixture, BuildSpecialTest) {
    field.build_tower(EntityType::TypeSpecial);
    EXPECT_EQ(typeid(*field.get_tower()), typeid(Special));

    field.get_tower()->attack();
    EXPECT_EQ(cb->att_calls, 1);
    field.get_tower()->die();
    EXPECT_EQ(cb->die_calls, 1);
}

TEST_F(FieldFixture, RemoveTowerTest) {
    EXPECT_ANY_THROW(field.remove_tower()) << "Removing nothing should throw exception";

    field.build_tower(EntityType::TypeFactory);
    field.remove_tower();

    EXPECT_FALSE(field.get_tower());
    EXPECT_EQ(field.get_team_status(), Team::Neutral);
    EXPECT_TRUE(field.get_moving_entities().empty());
}

TEST_F(FieldFixture, UpgradeTest) {
    EXPECT_ANY_THROW(field.upgrade_tower()) << "Updating nothing should throw exception";

    field.build_tower(EntityType::TypeFactory);

    EXPECT_FALSE(field.get_tower()->is_upgraded());

    field.upgrade_tower();

    EXPECT_TRUE(field.get_tower()->is_upgraded());
    EXPECT_EQ(field.get_team_status(), Team::Friendly);
    EXPECT_TRUE(field.get_moving_entities().empty());

    EXPECT_ANY_THROW(field.upgrade_tower()) << "Double upgrade should throw exception";
}

TEST_F(FieldFixture, UpdateTest) {
    //    TODO
}

TEST_F(FieldFixture, AddEntityTest) {
    EXPECT_EQ(field.get_moving_entities().size(), 0);
    field.add_moving_entity(std::make_shared<Alien>(Alien({0, 0}, cb, 0)));
    EXPECT_EQ(field.get_moving_entities().size(), 1);
    field.add_moving_entity(std::make_shared<Octopus>(Octopus({0, 0}, cb, 0)));
    EXPECT_EQ(field.get_moving_entities().size(), 2);
    field.add_moving_entity(std::make_shared<Robot>(Robot({0, 0}, cb, 0)));
    EXPECT_EQ(field.get_moving_entities().size(), 3);
}

TEST_F(FieldFixture, RemoveEntityTest) {
    field.add_moving_entity(std::make_shared<Alien>(Alien({0, 0}, cb, 0)));
    field.add_moving_entity(std::make_shared<Octopus>(Octopus({0, 0}, cb, 0)));
    field.add_moving_entity(std::make_shared<Robot>(Robot({0, 0}, cb, 0)));
    field.remove_entity_at(0);
    EXPECT_EQ(field.get_moving_entities().size(), 2);
    field.remove_entity_at(0);
    EXPECT_EQ(field.get_moving_entities().size(), 1);
    field.remove_entity_at(0);
    EXPECT_EQ(field.get_moving_entities().size(), 0);
}

class FactoryFixture : public ::testing::Test {
protected:
    std::shared_ptr<MockCallback> cb;
    std::shared_ptr<Factory> factory;
    FactoryFixture() : cb(new MockCallback()), factory(new Factory({0, 0}, cb)) {}
};

TEST_F(FactoryFixture, InitTest) {
    EXPECT_EQ(factory->attack_speed(), Constants::FACTORY_ATTACK_SPEED);
    EXPECT_EQ(factory->production_speed(), Constants::FACTORY_BASE_PRODUCTION_SPEED);
    EXPECT_EQ(factory->cost(), Constants::FACTORY_BASE_COST);
    EXPECT_EQ(factory->upgrade_cost(), Constants::FACTORY_UPGRADE_COST);
    EXPECT_EQ(factory->max_hp(), Constants::FACTORY_MAX_HP);
    EXPECT_EQ(factory->production_amount(), Constants::FACTORY_BASE_PRODUCTION);
    EXPECT_EQ(factory->remove_value(), Constants::FACTORY_BASE_REMOVE_VALUE);
    EXPECT_EQ(factory->get_position(), ((Coordinate){0, 0}));
    EXPECT_EQ(factory->get_vector_pos(), -1);
    EXPECT_FALSE(factory->is_upgraded());
    EXPECT_TRUE(factory->is_friendly());
}

TEST_F(FactoryFixture, UpgradeTest) {
    factory->upgrade();
    EXPECT_EQ(factory->attack_speed(), Constants::FACTORY_ATTACK_SPEED);
    EXPECT_EQ(factory->production_speed(), Constants::FACTORY_UPGRADE_PRODUCTION_SPEED);
    EXPECT_EQ(factory->cost(), Constants::FACTORY_UPGRADE_COST);
    EXPECT_EQ(factory->upgrade_cost(), Constants::FACTORY_UPGRADE_COST);
    EXPECT_EQ(factory->max_hp(), Constants::FACTORY_MAX_HP);
    EXPECT_EQ(factory->production_amount(), Constants::FACTORY_UPGRADE_PRODUCTION);
    EXPECT_EQ(factory->remove_value(), Constants::FACTORY_UPGRADE_REMOVE_VALUE);
    EXPECT_EQ(factory->get_position(), ((Coordinate){0, 0}));
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
    LaserTowerFixture() : cb(new MockCallback()), laserTower(new LaserTower({0, 0}, cb)) {}
};

TEST_F(LaserTowerFixture, InitTest) {
    EXPECT_EQ(laserTower->attack_speed(), Constants::LASERTOWER_BASE_ATTACKSPEED);
    EXPECT_EQ(laserTower->damage(), Constants::LASERTOWER_BASE_DAMAGE);
    EXPECT_EQ(laserTower->cost(), Constants::LASERTOWER_BASE_COST);
    EXPECT_EQ(laserTower->remove_value(), Constants::LASERTOWER_BASE_REMOVE_VALUE);
    EXPECT_EQ(laserTower->upgrade_cost(), Constants::LASERTOWER_UPGRADE_COST);
    EXPECT_EQ(laserTower->max_hp(), Constants::LASERTOWER_MAX_HP);
    EXPECT_EQ(laserTower->get_position(), ((Coordinate){0, 0}));
    EXPECT_EQ(laserTower->get_vector_pos(), -1);
    EXPECT_FALSE(laserTower->is_upgraded());
    EXPECT_TRUE(laserTower->is_friendly());
}

TEST_F(LaserTowerFixture, UpgradeTest) {
    laserTower->upgrade();
    EXPECT_EQ(laserTower->attack_speed(), Constants::LASERTOWER_UPGRADE_ATTACKSPEED);
    EXPECT_EQ(laserTower->cost(), Constants::LASERTOWER_UPGRADE_COST);
    EXPECT_EQ(laserTower->upgrade_cost(), Constants::LASERTOWER_UPGRADE_COST);
    EXPECT_EQ(laserTower->max_hp(), Constants::LASERTOWER_MAX_HP);
    EXPECT_EQ(laserTower->remove_value(), Constants::LASERTOWER_UPGRADE_REMOVE_VALUE);
    EXPECT_EQ(laserTower->get_position(), ((Coordinate){0, 0}));
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
    SniperTowerFixture() : cb(new MockCallback()), sniperTower(new SniperTower({0, 0}, cb)) {}
};

TEST_F(SniperTowerFixture, InitTest) {
    EXPECT_EQ(sniperTower->attack_speed(), Constants::SNIPERTOWER_BASE_ATTACKSPEED);
    EXPECT_EQ(sniperTower->damage(), Constants::SNIPERTOWER_BASE_DAMAGE);
    EXPECT_EQ(sniperTower->cost(), Constants::SNIPERTOWER_BASE_COST);
    EXPECT_EQ(sniperTower->remove_value(), Constants::SNIPERTOWER_BASE_REMOVE_VALUE);
    EXPECT_EQ(sniperTower->upgrade_cost(), Constants::SNIPERTOWER_UPGRADE_COST);
    EXPECT_EQ(sniperTower->max_hp(), Constants::SNIPERTOWER_MAX_HP);
    EXPECT_EQ(sniperTower->get_position(), ((Coordinate){0, 0}));
    EXPECT_EQ(sniperTower->get_vector_pos(), -1);
    EXPECT_FALSE(sniperTower->is_upgraded());
    EXPECT_TRUE(sniperTower->is_friendly());
}

TEST_F(SniperTowerFixture, UpgradeTest) {
    sniperTower->upgrade();
    EXPECT_EQ(sniperTower->attack_speed(), Constants::SNIPERTOWER_UPGRADE_ATTACKSPEED);
    EXPECT_EQ(sniperTower->cost(), Constants::SNIPERTOWER_UPGRADE_COST);
    EXPECT_EQ(sniperTower->upgrade_cost(), Constants::SNIPERTOWER_UPGRADE_COST);
    EXPECT_EQ(sniperTower->max_hp(), Constants::SNIPERTOWER_MAX_HP);
    EXPECT_EQ(sniperTower->remove_value(), Constants::SNIPERTOWER_UPGRADE_REMOVE_VALUE);
    EXPECT_EQ(sniperTower->get_position(), ((Coordinate){0, 0}));
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
    TeslaCoilFixture() : cb(new MockCallback()), teslaCoil(new TeslaCoil({0, 0}, cb)) {}
};

TEST_F(TeslaCoilFixture, InitTest) {
    EXPECT_EQ(teslaCoil->attack_speed(), Constants::TESLACOIL_BASE_ATTACKSPEED);
    EXPECT_EQ(teslaCoil->damage(), Constants::TESLACOIL_BASE_DAMAGE);
    EXPECT_EQ(teslaCoil->cost(), Constants::TESLACOIL_BASE_COST);
    EXPECT_EQ(teslaCoil->remove_value(), Constants::TESLACOIL_BASE_REMOVE_VALUE);
    EXPECT_EQ(teslaCoil->upgrade_cost(), Constants::TESLACOIL_UPGRADE_COST);
    EXPECT_EQ(teslaCoil->max_hp(), Constants::TESLACOIL_MAX_HP);
    EXPECT_EQ(teslaCoil->get_position(), ((Coordinate){0, 0}));
    EXPECT_EQ(teslaCoil->get_vector_pos(), -1);
    EXPECT_FALSE(teslaCoil->is_upgraded());
    EXPECT_TRUE(teslaCoil->is_friendly());
}

TEST_F(TeslaCoilFixture, UpgradeTest) {
    teslaCoil->upgrade();
    EXPECT_EQ(teslaCoil->attack_speed(), Constants::TESLACOIL_UPGRADE_ATTACKSPEED);
    EXPECT_EQ(teslaCoil->cost(), Constants::TESLACOIL_UPGRADE_COST);
    EXPECT_EQ(teslaCoil->upgrade_cost(), Constants::TESLACOIL_UPGRADE_COST);
    EXPECT_EQ(teslaCoil->max_hp(), Constants::TESLACOIL_MAX_HP);
    EXPECT_EQ(teslaCoil->remove_value(), Constants::TESLACOIL_UPGRADE_REMOVE_VALUE);
    EXPECT_EQ(teslaCoil->get_position(), ((Coordinate){0, 0}));
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

#pragma clang diagnostic pop
