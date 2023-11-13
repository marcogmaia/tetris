
// Copyright (c) Maia
#pragma once

#include "maia/tetris/grid.h"
#include "maia/tetris/shape.h"

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
    }
  }

  const Grid& grid() const {
    return grid_;
  }

  const Shape& CurrentShape() const {
    return current_shape_;
  }

  void Reset() {
    grid_ = Grid{};
    NextShape();
  }

 private:
  Shape GetShape() {
    auto shape = maia::Tetrominos::GetRandom();
    maia::SetPosition(2, 20, shape);
    return shape;
  }

  void NextShape() {
    current_shape_ = next_shape_;
    next_shape_ = GetShape();
  }

  Grid grid_{};
  Shape current_shape_;
  Shape next_shape_;
};

}  // namespace maia
