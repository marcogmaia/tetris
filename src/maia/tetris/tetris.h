
// Copyright (c) Maia
#pragma once

#include "maia/tetris/grid.h"
#include "maia/tetris/shape.h"

namespace maia {

class Tetris {
 public:
 private:
  Grid grid_;
  Shape current_shape_;
};

}  // namespace maia
