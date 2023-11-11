// Copyright (c) Maia

#pragma once

#include <raylib.h>

#include <vector>

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
  Block& at(int x, int y) {
    return grid_[x + kWithd * y];
  }

 private:
  static constexpr int kWithd = 10;
  static constexpr int kHeight = 20;
  //  This is stored in row major order.
  std::vector<Block> grid_;
};

}  // namespace maia
