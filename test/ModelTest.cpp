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
  // EXPECT_EQ(game_model.getPoints(), 0);
  // EXPECT_EQ(game_model.getWaveNumber(), 0);
  // EXPECT_EQ(game_model.getWaveProgress(), 0);
  // EXPECT_EQ(game_model.getGold(), 0);
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 12; ++j) {
      // EXPECT_FALSE((game_model.getField()[i][j]).tower)
      // EXPECT_TRUE((game_model.getField()[i][j]).movingEntities.empty())
      // EXPECT_EQ((game_model.getField()[i][j]).teamStatus, Team::Neutral)
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
