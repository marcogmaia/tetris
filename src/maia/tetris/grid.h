// Copyright (c) Maia

#pragma once

#include <vector>

#include <raylib.h>
#include <tl/optional.hpp>

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
  tl::optional<std::reference_wrapper<Block>> at(int x, int y) {
    if (!IsIndexInGridRange(GetIndex(x, y))) {
      return {};
    }
    return grid_[x + kWidth * y];
  }

  const Block &at(int x, int y) const {
    return grid_[x + kWidth * y];
  }

  constexpr static int GridWidth() {
    return kWidth;
  }

  constexpr static int GridHeight() {
    return kHeight;
  }

  bool CheckCollision(const Shape &shape);

  void FillWith(const Shape &shape) {
    for (const auto &pos : shape.positions) {
      if (auto block = at(pos.x, pos.y)) {
        block->get() = Block{
            .color = shape.color,
            .filled = true,
        };
      }
    }
  }

  std::vector<Block> &grid() {
    return grid_;
  }

  const std::vector<Block> &grid() const {
    return grid_;
  }

 private:
  static int GetIndex(int x, int y) {
    return x + y * kWidth;
  }

  bool IsIndexInGridRange(int index) {
    return 0 <= index && index < grid_.size();
  }

  static constexpr int kWidth = 10;
  static constexpr int kHeight = 20;
  //  This is stored in row major order.
  std::vector<Block> grid_ = std::vector<Block>(kWidth * kHeight, Block{});
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
