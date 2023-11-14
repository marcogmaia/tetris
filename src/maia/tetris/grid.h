// Copyright (c) Maia

#pragma once

#include <span>
#include <vector>

#include <raylib.h>
#include <tl/optional.hpp>

#include "maia/tetris/tetromino.h"

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

  bool CheckCollision(const Tetromino &shape);

  void FillWith(const Tetromino &shape) {
    for (const auto &pos : shape.positions) {
      if (auto block = at(std::lroundf(pos.x), std::lroundf(pos.y))) {
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

  std::vector<std::span<Block>> rows() {
    return rows_;
  }

 private:
  static int GetIndex(int x, int y) {
    return x + y * kWidth;
  }

  bool IsIndexInGridRange(int index) {
    return 0 <= index && index < grid_.size();
  }

  std::span<Block> GetGridRow(int index) {
    const auto begin_row = std::next(grid_.begin(), index * Grid::GridWidth());
    const auto end_row = std::next(begin_row, Grid::GridWidth());
    return std::span<Block>(begin_row, end_row);
  }

  static std::vector<std::span<Block>> InitRows(std::vector<Block> &grid) {
    const auto get_grid_row = [&grid](int index) -> std::span<Block> {
      const auto begin_row = std::next(grid.begin(), index * Grid::GridWidth());
      const auto end_row = std::next(begin_row, Grid::GridWidth());
      return std::span<Block>(begin_row, end_row);
    };

    std::vector<std::span<Block>> rows;
    rows.reserve(Grid::GridHeight());
    for (int row = 0; row < Grid::GridHeight(); ++row) {
      rows.emplace_back(get_grid_row(row));
    }
    return rows;
  }

  static constexpr int kWidth = 10;
  static constexpr int kHeight = 20;
  //  This is stored in row major order.
  std::vector<Block> grid_ = std::vector<Block>(kWidth * kHeight, Block{});
  std::vector<std::span<Block>> rows_ = InitRows(grid_);
  ;
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
