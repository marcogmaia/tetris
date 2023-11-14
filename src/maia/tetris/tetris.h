
// Copyright (c) Maia
#pragma once

#include <algorithm>
#include <iterator>
#include <span>

#include "maia/tetris/grid.h"
#include "maia/tetris/tetromino.h"

namespace maia {

class Tetris {
 public:
  Tetris() {
    current_shape_ = GetShape();
    next_shape_ = GetShape();
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

  Tetromino& CurrentShape() {
    return current_shape_;
  }

  const Tetromino& CurrentShape() const {
    return current_shape_;
  }

  void Reset() {
    grid_ = Grid{};
    NextShape();
  }

  void Move(int x, int y) {
    if (auto next_pos = ::maia::Move(current_shape_, x, y); CanMove(next_pos)) {
      current_shape_ = next_pos;
    }
  }

  void RotateLeft() {
    if (auto next_rotation = RotateShapeLeft(current_shape_); CanMove(next_rotation)) {
      current_shape_ = next_rotation;
    }
  }

 private:
  bool CanMove(const Tetromino& shape) {
    auto can_move = [this](Position pos) {
      const auto x = std::lroundf(pos.x);
      const auto y = std::lroundf(pos.y);
      const auto block = grid_.at(x, y);
      if (x < 0.0 || x >= Grid::GridWidth()) {
        return false;
      }
      if (!block) {
        return true;
      }
      return !block->get().filled;
    };
    return std::all_of(shape.positions.begin(), shape.positions.end(), can_move);
  }

  static Tetromino GetShape() {
    auto shape = maia::Tetrominos::GetRandom();
    maia::SetPosition(2, 20, shape);
    return shape;
  }

  void RemoveFilledRows() {
    const auto is_filled = [](std::span<Block> row) {
      return std::all_of(row.begin(), row.end(), [](const Block& block) { return block.filled; });
    };

    auto rows = grid_.rows();
    std::stable_sort(rows.begin(), rows.end(), [is_filled](std::span<Block> lhs, std::span<Block> rhs) {
      return !is_filled(lhs) && is_filled(rhs);
    });

    Grid new_grid{};
    for (int i = 0; auto& row : rows) {
      if (is_filled(row)) {
        std::fill(row.begin(), row.end(), Block{});
      }
      std::copy(row.begin(), row.end(), new_grid.rows()[i].begin());
      ++i;
    }
    grid_ = std::move(new_grid);
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
  Tetromino current_shape_;
  Tetromino next_shape_;
};

}  // namespace maia
