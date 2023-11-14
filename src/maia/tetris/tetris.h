
// Copyright (c) Maia
#pragma once

#include <algorithm>
#include <iterator>
#include <span>

#include "maia/tetris/grid.h"
#include "maia/tetris/shape.h"

namespace maia {

class Tetris {
 public:
  Tetris() {
    current_shape_ = GetShape();
    next_shape_ = GetShape();

    rows_.reserve(Grid::GridHeight());
    for (int row = 0; row < Grid::GridHeight(); ++row) {
      rows_.emplace_back(GetGridRow(row));
    }
  }

  void Tick() {
    auto prev = current_shape_;
    current_shape_.Move(0, -1);
    if (grid_.CheckCollision(current_shape_)) {
      grid_.FillWith(prev);
      NextShape();
      RemoveFilledRows();
    }
  }

  const Grid& grid() const {
    return grid_;
  }

  Shape& CurrentShape() {
    return current_shape_;
  }

  const Shape& CurrentShape() const {
    return current_shape_;
  }

  void Reset() {
    grid_ = Grid{};
    NextShape();
  }

 private:
  static Shape GetShape() {
    auto shape = maia::Tetrominos::GetRandom();
    maia::SetPosition(2, 20, shape);
    return shape;
  }

  void RemoveFilledRows() {
    const auto is_filled = [](std::span<Block> row) {
      return std::all_of(row.begin(), row.end(), [](const Block& block) { return block.filled; });
    };

    auto rows = rows_;
    std::stable_sort(rows.begin(), rows.end(), [is_filled](std::span<Block> lhs, std::span<Block> rhs) {
      return !is_filled(lhs) && is_filled(rhs);
    });

    std::vector<Block> new_grid;
    new_grid.reserve(grid_.grid().size());
    for (auto& row : rows) {
      if (is_filled(row)) {
        std::fill(row.begin(), row.end(), Block{});
      }
      std::copy(row.begin(), row.end(), std::back_inserter(new_grid));
    }

    std::copy(new_grid.begin(), new_grid.end(), grid_.grid().begin());
  }

  void NextShape() {
    current_shape_ = next_shape_;
    next_shape_ = GetShape();
  }

  std::span<Block> GetGridRow(int index) {
    const auto begin_row = std::next(grid_.grid().begin(), index * Grid::GridWidth());
    const auto end_row = std::next(begin_row, Grid::GridWidth());
    return std::span<Block>(begin_row, end_row);
  }

  Grid grid_{};
  Shape current_shape_;
  Shape next_shape_;

  std::vector<std::span<Block>> rows_;
};

}  // namespace maia
