// Copyright (c) Maia

#pragma once

#include <algorithm>
#include <vector>

#include <raylib.h>

// #include "maia/tetris/shape.h"
#include "shape.h"

namespace maia {

struct Block {
  Color color;
  bool filled;
  bool frozen;
};

// Order:
// y=19 - 190...199
// y=.. -  | ....|
// y=2  -  20....39
// y=1  -  10....19
// y=0  -   0.....9
//     x =  |    |
class Grid {
 public:
  Block &at(int x, int y) {
    return grid_[x + kWithd * y];
  }

  void Move(Shape &shape) {
    Shape current = shape;
    maia::Move(0, 1, shape);
    if (!CheckColision(shape)) {
      return;
    }
    FillWith(current);
  }

  constexpr static int GridWidth() {
    return kWithd;
  }

  constexpr static int GridHeight() {
    return kHeight;
  }

 private:
  void FillWith(const Shape &shape) {
    for (const auto &pos : shape.positions) {
      at(pos.x, pos.y) = Block{
          .color = shape.color,
          .filled = true,
          .frozen = true,
      };
    }
  }

  bool CheckColision(const Shape &shape) {
    return std::any_of(shape.positions.cbegin(), shape.positions.cend(), [this](const Position &pos) {
      return pos.y == 0 || at(pos.x, pos.y).filled;
    });
  }

  static constexpr int kWithd = 10;
  static constexpr int kHeight = 20;
  //  This is stored in row major order.
  std::vector<Block> grid_;
};

}  // namespace maia
