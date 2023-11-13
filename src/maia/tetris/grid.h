// Copyright (c) Maia

#pragma once

#include <algorithm>
#include <vector>

#include <raylib.h>

// #include "maia/tetris/shape.h"
#include "shape.h"

namespace maia {

struct Block {
  Color color{};
  bool filled{};
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

  const Block &at(int x, int y) const {
    return grid_[x + kWithd * y];
  }

  constexpr static int GridWidth() {
    return kWithd;
  }

  constexpr static int GridHeight() {
    return kHeight;
  }

  bool CheckCollision(const Shape &shape) {
    return std::any_of(shape.positions.cbegin(), shape.positions.cend(), [this](const Position &pos) {
      if (pos.y >= kHeight) {
        return false;
      }
      return pos.y < 0 || at(lroundf(pos.x), lroundf(pos.y)).filled;
    });
  }

  void FillWith(const Shape &shape) {
    for (const auto &pos : shape.positions) {
      at(pos.x, pos.y) = Block{
          .color = shape.color,
          .filled = true,
      };
    }
  }

  std::vector<Block> &grid() {
    return grid_;
  }

  const std::vector<Block> &grid() const {
    return grid_;
  }

 private:
  static constexpr int kWithd = 10;
  static constexpr int kHeight = 20;
  //  This is stored in row major order.
  std::vector<Block> grid_ = std::vector<Block>(kWithd * kHeight, Block{});
};

inline void DrawGrid(const Grid &grid) {
  for (int x = 0; x < Grid::GridWidth(); ++x) {
    for (int y = 0; y < Grid::GridHeight(); ++y) {
      const auto &block = grid.at(x, y);
      if (block.filled) {
        constexpr int kSquareSide = 32;
        DrawRectangle(x * kSquareSide, y * kSquareSide, kSquareSide, kSquareSide, block.color);
      }
    }
  }
}

}  // namespace maia
