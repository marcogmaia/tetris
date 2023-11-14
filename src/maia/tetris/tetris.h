
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
    current_tetromino_ = GetTetromino();
    next_tetromino_ = GetTetromino();
  }

  void Tick() {
    auto prev = current_tetromino_;
    current_tetromino_.Move(0, -1);
    if (grid_.CheckCollision(current_tetromino_)) {
      grid_.FillWith(prev);
      NextTetromino();
      RemoveFilledRows();
    }
  }

  const Grid& grid() const {
    return grid_;
  }

  Tetromino& CurrentTetromino() {
    return current_tetromino_;
  }

  const Tetromino& Currenttetromino() const {
    return current_tetromino_;
  }

  void Reset() {
    grid_ = Grid{};
    NextTetromino();
  }

  void Move(int x, int y) {
    if (auto next_pos = ::maia::Move(current_tetromino_, x, y); CanMove(next_pos)) {
      current_tetromino_ = next_pos;
    }
  }

  void RotateLeft() {
    if (auto next_rotation = RotatetetrominoLeft(current_tetromino_); CanMove(next_rotation)) {
      current_tetromino_ = next_rotation;
    }
  }

 private:
  bool CanMove(const Tetromino& tetromino) {
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
    return std::all_of(tetromino.positions.begin(), tetromino.positions.end(), can_move);
  }

  static Tetromino GetTetromino() {
    auto tetromino = maia::Tetrominos::GetRandom();
    maia::SetPosition(2, 20, tetromino);
    return tetromino;
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

  void NextTetromino() {
    current_tetromino_ = next_tetromino_;
    next_tetromino_ = GetTetromino();
  }

  std::span<Block> GetGridRow(int index) {
    const auto begin_row = std::next(grid_.grid().begin(), index * Grid::GridWidth());
    const auto end_row = std::next(begin_row, Grid::GridWidth());
    return std::span<Block>(begin_row, end_row);
  }

  Grid grid_{};
  Tetromino current_tetromino_;
  Tetromino next_tetromino_;
};

}  // namespace maia
