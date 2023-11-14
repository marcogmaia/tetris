// Copyright (c) Maia

#pragma once

#include <algorithm>
#include <array>
#include <numbers>

#include <raylib.h>

#include "maia/tetris/vector.h"

namespace maia {

using Position = Vector2<float>;

struct Shape {
  Color color;
  // Occupied positions by the shape.
  std::array<Position, 4> positions;
  Position center;
  // Check if the shape can be moved.
  bool can_move = true;

  Shape &Move(Position::Type dx, Position::Type dy) {
    for (auto &pos : positions) {
      pos.x += dx;
      pos.y += dy;
    }
    center = center + Position{dx, dy};
    return *this;
  }
};

struct Tetrominos {
  // https://www.wikiwand.com/en/Tetromino
  // clang-format off
  static constexpr std::array<Shape, 5> kTetrominos{
      Shape{  .color{BLUE}, .positions{{{0, 0}, {1, 0}, {2, 0}, {3, 0}}}, .center{1.5, -0.5}}, // KStraight
      Shape{.color{YELLOW}, .positions{{{0, 0}, {0, 1}, {1, 0}, {1, 1}}}, .center{0.5,  0.5}}, // kSquare
      Shape{  .color{PINK}, .positions{{{0, 1}, {1, 1}, {2, 1}, {1, 0}}}, .center{1.0,  1.0}}, // kT
      Shape{.color{ORANGE}, .positions{{{0, 0}, {0, 1}, {0, 2}, {1, 0}}}, .center{0.0,  0.0}}, // kL
      Shape{ .color{GREEN}, .positions{{{0, 0}, {1, 0}, {1, 1}, {2, 1}}}, .center{1.0,  1.0}}, // kSkew
  };
  // clang-format on

  static constexpr std::array<int, 5> kCenterIndex{1, 2, 3, 1, 2};

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

inline Position GetCenter(const Shape &shape) {
  const auto &positions = shape.positions;
  const auto [xmin, xmax] = std::minmax_element(
      positions.begin(), positions.end(), [](const Position &pos0, const Position &pos1) { return pos0.x < pos1.x; });
  const auto [ymin, ymax] = std::minmax_element(
      positions.begin(), positions.end(), [](const Position &pos0, const Position &pos1) { return pos0.x < pos1.x; });
  return Position{
      (xmin->x + xmax->x) / 2.f,
      (ymin->y + ymax->y) / 2.f,
  };
}

inline Shape Move(Shape shape, Position::Type dx, Position::Type dy) {
  for (auto &pos : shape.positions) {
    pos += {dx, dy};
  }
  shape.center = shape.center + Position{dx, dy};
  return shape;
}

inline void SetPosition(float x, float y, Shape &shape) {
  for (auto &pos : shape.positions) {
    pos = pos + Position{x, y};
  }
  shape.center = shape.center + Position{x, y};
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

inline Shape RotateShape(const Shape &shape, float angle) {
  Shape out = shape;
  for (auto &position : out.positions) {
    position = Rotate(position, angle, shape.center);
  }
  return out;
}

inline Shape RotateShapeLeft(const Shape &shape) {
  return RotateShape(shape, 90);
}

inline Shape RotateShapeRight(const Shape &shape) {
  return RotateShape(shape, -90);
}

}  // namespace maia
