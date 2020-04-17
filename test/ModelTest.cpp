//
// Created by Boldizsár Poór (boldar99@gmail.com) on 2020. 03. 22..
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <gtest/gtest.h>
#include <model/Field.h>
#include <model/GameModel.h>
#include <model/Team.h>
#include <typeinfo>

class GameModelFixture : public ::testing::Test {
protected:
    GameModel game_model;
    GameModelFixture() : game_model() {}
};

TEST_F(GameModelFixture, InitTest) {
    EXPECT_EQ(game_model.get_points(), 0);
    EXPECT_EQ(game_model.get_wave_number(), 0);
    //EXPECT_EQ(game_model.get_wave_progress(), 0);
    EXPECT_EQ(game_model.get_gold(), 0);
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 12; ++j) {
            // EXPECT_FALSE(game_model.get_field({i, j}).get_tower());
            // EXPECT_TRUE(game_model.get_field({i, j}).get_moving_entities().empty());
            // EXPECT_EQ(game_model.get_field({i, j}).get_team_status(), Team::Neutral);
        }
    }
}

class FieldFixture : public ::testing::Test {
protected:
    Field field;
    FieldFixture() : field({0,0}, nullptr) {}
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
    field.build_tower(EntityType::TypeFactory);
    field.remove_tower();
    EXPECT_FALSE(field.get_tower());
    EXPECT_EQ(field.get_team_status(), Team::Neutral);
    EXPECT_TRUE(field.get_moving_entities().empty());
}

TEST_F(FieldFixture, UpgradeTest) {
    field.build_tower(EntityType::TypeFactory);
    EXPECT_FALSE(field.get_tower()->is_upgraded());
    field.upgrade_tower();
    EXPECT_TRUE(field.get_tower()->is_upgraded());
    EXPECT_EQ(field.get_team_status(), Team::Friendly);
    EXPECT_TRUE(field.get_moving_entities().empty());
}

TEST_F(FieldFixture, UpdateTest) {
//    TODO
}

TEST_F(FieldFixture, RemoveEntityTest) {
//    TODO
}

#pragma clang diagnostic pop
