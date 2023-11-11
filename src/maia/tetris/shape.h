// Copyright (c) Maia

#pragma once

#include <numbers>
#include <vector>

#include <raylib.h>

#include "maia/tetris/vector.h"

namespace maia {

using Position = Vector2<int>;

struct Shape {
  Color color;
  // Occupied positions by the shape.
  std::vector<Position> positions;
  // Check if the shape can be moved.
  bool frozen{};
};

inline void Move(int dx, int dy, Shape &shape) {
  for (auto &pos : shape.positions) {
    pos.x += dx;
    pos.y -= dy;
  }
}

inline constexpr Position Rotate(Position pos, float angle, Position center = {0, 0}) {
  constexpr float kPi = std::numbers::pi_v<float>;
  const auto rads = angle * kPi / 180.f;
  return (pos - center).Rotate(rads) + center;
}

inline Position RotateLeft(Position pos, Position center = {0, 0}) {
  return Rotate(pos, 90, center);
}

inline Position RotateRight(Position pos, Position center = {0, 0}) {
  return Rotate(pos, -90, center);
}

}  // namespace maia
