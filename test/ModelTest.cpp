//
// Created by Boldizsár Poór (boldar99@gmail.com) on 2020. 03. 22..
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <gtest/gtest.h>
#include <model/Constants.h>
#include <model/FieldEntityCallbackClass.h>
#include <model/Field.h>
#include <model/GameModel.h>
#include <model/Team.h>

#include <functional>

class MockCallback : public FieldEntityCallbackClass {
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
          FieldEntityCallbackClass(
              [this](const std::shared_ptr<FieldEntity>& obj) { ++pro_calls; },
              [this](const std::shared_ptr<Unstable>& obj) { ++mov_calls; },
              [this](const std::shared_ptr<FieldEntity>& obj) { ++att_calls; },
              [this](const std::shared_ptr<FieldEntity>& obj) { ++die_calls; }) {}
};

TEST(TestMockCallback, Test) {
    std::shared_ptr<MockCallback> cb;
    //TODO: with unstable
    Factory factory({0,0}, cb);
    LaserTower laser_tower({1,1}, cb);
    EXPECT_EQ(cb->pro_calls, 0);
    EXPECT_EQ(cb->mov_calls, 0);
    EXPECT_EQ(cb->att_calls, 0);
    EXPECT_EQ(cb->die_calls, 0);
    factory.produce();
    factory.die();
    EXPECT_EQ(cb->pro_calls, 1);
    EXPECT_EQ(cb->die_calls, 1);
}

class GameModelFixture : public ::testing::Test {
protected:
    GameModel game_model;
    GameModelFixture() : game_model() {}
};

TEST_F(GameModelFixture, InitTest) {
    EXPECT_EQ(game_model.get_points(), 0);
    EXPECT_EQ(game_model.get_wave_number(), 0);
    // EXPECT_EQ(game_model.get_wave_progress(), 0);
    EXPECT_EQ(game_model.get_gold(), 0);
    /*
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 12; ++j) {
            // EXPECT_FALSE(game_model.get_field({i, j}).get_tower());
            // EXPECT_TRUE(game_model.get_field({i, j}).get_moving_entities().empty());
            // EXPECT_EQ(game_model.get_field({i, j}).get_team_status(), Team::Neutral);
        }
    }
    */
}

class FieldFixture : public ::testing::Test {
protected:
    Field field;
    FieldFixture() : field({0, 0}, nullptr) {}
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
}

TEST_F(FieldFixture, BuildLaserTowerTest) {
    field.build_tower(EntityType::TypeLaserTower);
    EXPECT_EQ(typeid(*field.get_tower()), typeid(LaserTower));
}

TEST_F(FieldFixture, BuildTeslaCoilTest) {
    field.build_tower(EntityType::TypeTeslaCoil);
    EXPECT_EQ(typeid(*field.get_tower()), typeid(TeslaCoil));
}

TEST_F(FieldFixture, BuildSniperTowerTest) {
    field.build_tower(EntityType::TypeSniperTower);
    EXPECT_EQ(typeid(*field.get_tower()), typeid(SniperTower));
}

TEST_F(FieldFixture, BuildSpecialTest) {
    field.build_tower(EntityType::TypeSpecial);
    EXPECT_EQ(typeid(*field.get_tower()), typeid(Special));
}

TEST_F(FieldFixture, RemoveTowerTest) {
    EXPECT_ANY_THROW(field.remove_tower()) << "Removeing nothing should throw exception";

    field.build_tower(EntityType::TypeFactory);
    field.remove_tower();

    EXPECT_FALSE(field.get_tower());
    EXPECT_EQ(field.get_team_status(), Team::Neutral);
    EXPECT_TRUE(field.get_moving_entities().empty());
}

TEST_F(FieldFixture, UpgradeTest) {
    EXPECT_ANY_THROW(field.upgrade_tower()) << "Updateing nothing should throw exception";

    field.build_tower(EntityType::TypeFactory);

    EXPECT_FALSE(field.get_tower()->is_upgraded());

    field.upgrade_tower();

    EXPECT_TRUE(field.get_tower()->is_upgraded());
    EXPECT_EQ(field.get_team_status(), Team::Friendly);
    EXPECT_TRUE(field.get_moving_entities().empty());

    EXPECT_ANY_THROW(field.upgrade_tower()) << "Duble upgrade should throw exception";
}

TEST_F(FieldFixture, UpdateTest) {
    //    TODO
}

TEST_F(FieldFixture, RemoveEntityTest) {
    //    Can change team_status, but not implemented
    //    TODO
}

class FactoryFixture : public ::testing::Test {
protected:
    std::shared_ptr<MockCallback> cb;
    Factory factory;
    FactoryFixture() : cb(new MockCallback()), factory({0, 0}, cb) {}
};

TEST_F(FactoryFixture, InitTest) {
    EXPECT_EQ(factory.attack_speed(), Constants::FACTORY_ATTACK_SPEED);
    EXPECT_EQ(factory.production_speed(), Constants::FACTORY_BASE_PRODUCTION_SPEED);
    EXPECT_EQ(factory.cost(), Constants::FACTORY_BASE_COST);
    EXPECT_EQ(factory.upgrade_cost(), Constants::FACTORY_UPGRADE_COST);
    EXPECT_EQ(factory.max_hp(), Constants::FACTORY_BASE_MAX_HP);
    EXPECT_EQ(factory.production_amount(), Constants::FACTORY_UPGRADE_PRODUCTION);
    EXPECT_EQ(factory.remove_value(), Constants::FACTORY_BASE_REMOVE_VALUE);
    EXPECT_EQ(factory.get_position(), ((Coordinate){0, 0}));
    EXPECT_EQ(factory.get_damage(), 0);
    EXPECT_EQ(factory.get_vector_pos(), -1);
    EXPECT_FALSE(factory.is_upgraded());
    EXPECT_TRUE(factory.is_friendly());
}

TEST_F(FactoryFixture, CallBackTest) {
    factory.produce();
    EXPECT_EQ(cb->pro_calls, 1);
    EXPECT_EQ(cb->die_calls, 0);
    factory.die();
    EXPECT_EQ(cb->pro_calls, 1);
    EXPECT_EQ(cb->die_calls, 1);
}

#pragma clang diagnostic pop
