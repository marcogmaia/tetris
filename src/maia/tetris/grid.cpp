
// Copyright (c) Maia

#include "maia/tetris/grid.h"

namespace maia {

bool Grid::CheckCollision(const Tetromino &shape) {
  return std::any_of(shape.positions.cbegin(), shape.positions.cend(), [this](const Position &pos) {
    int x = std::lroundf(pos.x);
    int y = std::lroundf(pos.y);
    if (y < 0) {
      return true;
    }

    int index = GetIndex(x, y);
    if (!IsIndexInGridRange(index)) {
      return false;
    }
    return grid_[index].filled;
  });
}

}  // namespace maia
