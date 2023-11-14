// Copyright (c) Maia

#include "maia/tetris/tetromino.h"

#include <vector>

#include <gtest/gtest.h>

namespace maia {

TEST(Tetromino, Rotate) {
  std::vector<Position> expecteds{
      { 0,  1},
      {-1,  0},
      { 0, -1},
      { 1,  0}
  };
  for (Position pos{1, 0}; auto &expected : expecteds) {
    pos = Rotate(pos, 90);
    EXPECT_NEAR(pos.x, expected.x, 1e-6);
    EXPECT_NEAR(pos.y, expected.y, 1e-6);
  }
}

TEST(Tetromino, RotateStraight) {
  auto tetromino = Tetrominos::Get(Tetrominos::Format::kStraight);
  auto rotated_tetromino = RotatetetrominoLeft(tetromino);
  auto expected_positions = std::vector<Position>{
      {1, -2},
      {1, -1},
      {1,  0},
      {1,  1}
  };
  ASSERT_EQ(expected_positions.size(), rotated_tetromino.positions.size());
  for (int i = 0; i < expected_positions.size(); ++i) {
    EXPECT_NEAR(expected_positions[i].x, rotated_tetromino.positions[i].x, 1e-6);
    EXPECT_NEAR(expected_positions[i].y, rotated_tetromino.positions[i].y, 1e-6);
  }
}

}  // namespace maia
