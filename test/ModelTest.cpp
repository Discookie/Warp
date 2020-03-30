//
// Created by Boldizsár Poór (boldar99@gmail.com) on 2020. 03. 22..
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <gtest/gtest.h>
#include <model/Field.h>
#include <model/GameModel.h>
#include <model/Team.h>

class GameModelFixture : public ::testing::Test {
protected:
    GameModel game_model;
    GameModelFixture() : game_model() {}
};

TEST_F(GameModelFixture, InitTest) {
    EXPECT_EQ(game_model.get_points(), 0);
    EXPECT_EQ(game_model.get_wave_number(), 0);
    EXPECT_EQ(game_model.get_wave_progress(), 0);
    EXPECT_EQ(game_model.get_gold(), 0);
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 12; ++j) {
            EXPECT_EQ(game_model.get_field({i, j}).get_tower(), nullptr);
            EXPECT_TRUE(game_model.get_field({i, j}).get_moving_entities().empty());
            EXPECT_EQ(game_model.get_field({i, j}).get_team_status(), Team::Neutral);
        }
    }
}

class FieldFixture : public ::testing::Test {
protected:
    Field field;
    FieldFixture() : field() {}
};

TEST_F(FieldFixture, InitTest) {}

#pragma clang diagnostic pop
