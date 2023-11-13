// Copyright (c) Maia

#include "maia/tetris/shape.h"

#include <vector>

#include <gtest/gtest.h>

namespace maia {

TEST(Shape, Rotate) {
  constexpr int kUnit = 100;
  std::vector<Position> expecteds{
      {     0,  kUnit},
      {-kUnit,      0},
      {     0, -kUnit},
      { kUnit,      0}
  };
  for (Position pos{kUnit, 0}; auto &expected : expecteds) {
    pos = Rotate(pos, 90);
    EXPECT_EQ(pos.x, expected.x);
    EXPECT_EQ(pos.y, expected.y);
  }
}

TEST(Shape, RotateStraight) {
  auto shape = Tetrominos::Get(Tetrominos::Tetromino::kStraight);
}

}  // namespace maia
