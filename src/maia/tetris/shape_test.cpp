// Copyright (c) Maia

#include "maia/tetris/shape.h"

#include <vector>

#include <gtest/gtest.h>

namespace maia {

TEST(Shape, Rotate) {
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

TEST(Shape, RotateStraight) {
  auto shape = Tetrominos::Get(Tetrominos::Tetromino::kStraight);
  auto rotated_shape = RotateShapeLeft(shape);
  auto expected_positions = std::vector<Position>{
      {1, -2},
      {1, -1},
      {1,  0},
      {1,  1}
  };
  ASSERT_EQ(expected_positions.size(), rotated_shape.positions.size());
  for (int i = 0; i < expected_positions.size(); ++i) {
    EXPECT_NEAR(expected_positions[i].x, rotated_shape.positions[i].x, 1e-6);
    EXPECT_NEAR(expected_positions[i].y, rotated_shape.positions[i].y, 1e-6);
  }
}

}  // namespace maia
