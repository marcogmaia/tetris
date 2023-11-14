// Copyright (c) Maia

#pragma once

#include <algorithm>
#include <array>
#include <numbers>

#include <raylib.h>

#include "maia/tetris/vector.h"

namespace maia {

using Position = Vector2<float>;

struct Tetromino {
  Color color;
  // Occupied positions by the shape.
  std::array<Position, 4> positions;
  Position center;
  // Check if the shape can be moved.
  bool can_move = true;

  Tetromino &Move(Position::Type dx, Position::Type dy) {
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
  static constexpr std::array<Tetromino, 7> kTetrominos{
      Tetromino{.color{SKYBLUE}, .positions{{{0, 0}, {1, 0}, {2, 0}, {3, 0}}}, .center{1.5, -0.5}}, // kStraight
      Tetromino{   .color{BLUE}, .positions{{{0, 0}, {1, 0}, {1, 1}, {1, 2}}},  .center{1.0, 1.0}}, // kJ
      Tetromino{ .color{ORANGE}, .positions{{{0, 0}, {0, 1}, {0, 2}, {1, 0}}},  .center{0.0, 1.0}}, // kL
      Tetromino{ .color{YELLOW}, .positions{{{0, 0}, {0, 1}, {1, 0}, {1, 1}}},  .center{0.5, 0.5}}, // kSquare
      Tetromino{  .color{GREEN}, .positions{{{0, 0}, {1, 0}, {1, 1}, {2, 1}}},  .center{1.0, 1.0}}, // kS
      Tetromino{   .color{PINK}, .positions{{{0, 1}, {1, 1}, {2, 1}, {1, 0}}},  .center{1.0, 1.0}}, // kT
      Tetromino{    .color{RED}, .positions{{{0, 1}, {1, 1}, {1, 0}, {2, 0}}},  .center{1.0, 1.0}}, // kZ
  };

  static constexpr std::array<int, 5> kCenterIndex{1, 2, 3, 1, 2};

  enum class Format {
    kStraight = 0,
    kJ,
    kL,
    kSquare,
    kS,
    kT,
    kZ,
  };

  static constexpr Tetromino Get(Format tetromino) {
    static_assert(kTetrominos.size() - 1 == static_cast<size_t>(Format::kZ));
    return kTetrominos[static_cast<int>(tetromino)];
  }

  static Tetromino GetRandom() {
    return kTetrominos[GetRandomValue(0, kTetrominos.size() - 1)];
  }
};

inline Position GetCenter(const Tetromino &shape) {
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

inline Tetromino Move(Tetromino shape, Position::Type dx, Position::Type dy) {
  for (auto &pos : shape.positions) {
    pos += {dx, dy};
  }
  shape.center = shape.center + Position{dx, dy};
  return shape;
}

inline void SetPosition(float x, float y, Tetromino &shape) {
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

inline Tetromino RotateShape(const Tetromino &shape, float angle) {
  Tetromino out = shape;
  for (auto &position : out.positions) {
    position = Rotate(position, angle, shape.center);
  }
  return out;
}

inline Tetromino RotateShapeLeft(const Tetromino &shape) {
  return RotateShape(shape, 90);
}

inline Tetromino RotateShapeRight(const Tetromino &shape) {
  return RotateShape(shape, -90);
}

}  // namespace maia
