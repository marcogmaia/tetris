// Copyright (c) Maia

#pragma once

#include <array>
#include <numbers>

#include <raylib.h>

#include "maia/tetris/vector.h"

namespace maia {

using Position = Vector2<int>;

struct Shape {
  Color color;
  // Occupied positions by the shape.
  std::array<Position, 4> positions;
  // Check if the shape can be moved.
  bool frozen{};
};

struct Tetrominos {
  // https://www.wikiwand.com/en/Tetromino
  static constexpr std::array<Shape, 5> kTetrominos{
      Shape{  .color{BLUE}, .positions{Position{0, 0}, Position{1, 0}, Position{2, 0}, Position{3, 0}}, .frozen{}},
      Shape{.color{YELLOW}, .positions{Position{0, 0}, Position{0, 1}, Position{1, 0}, Position{1, 1}}, .frozen{}},
      Shape{  .color{PINK}, .positions{Position{0, 1}, Position{1, 1}, Position{2, 1}, Position{1, 0}}, .frozen{}},
      Shape{.color{ORANGE}, .positions{Position{0, 0}, Position{0, 1}, Position{0, 2}, Position{1, 0}}, .frozen{}},
      Shape{ .color{GREEN}, .positions{Position{0, 0}, Position{1, 0}, Position{1, 1}, Position{2, 1}}, .frozen{}},
  };

  enum class Tetromino {
    kStraight = 0,
    kSquare,
    kT,
    kL,
    kSkew,
  };

  static constexpr Shape Get(Tetromino tetromino) {
    static_assert(kTetrominos.size() - 1 == static_cast<size_t>(Tetromino::kSkew));
    return kTetrominos[static_cast<int>(tetromino)];
  }

  static Shape GetRandom() {
    return kTetrominos[GetRandomValue(0, kTetrominos.size() - 1)];
  }
};

inline void Move(int dx, int dy, Shape &shape) {
  for (auto &pos : shape.positions) {
    pos.x += dx;
    pos.y -= dy;
  }
}

inline void SetPosition(int x, int y, Shape &shape) {
  // const auto max = std::max_element(
  //     shape.positions.cbegin(), shape.positions.cend(), [](Position pos1, Position pos2) { return pos1.y > pos2.y;
  //     });
  for (auto &pos : shape.positions) {
    pos = pos + Position{x, y};
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
