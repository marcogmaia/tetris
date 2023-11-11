#pragma once

namespace maia {

template <typename T>
struct Vector2 {
  T x;
  T y;

  bool operator==(const Vector2<T> &) const = default;

  Vector2<T> operator+(const Vector2<T> rhs) const {
    return {x + rhs.x, y + rhs.y};
  };

  Vector2<T> operator-() const {
    return {-x, -y};
  };

  Vector2<T> operator-(const Vector2<T> rhs) const {
    return *this + (-rhs);
  };

  T dot(const Vector2<T> rhs) const {
    return x * rhs.x + y * rhs.y;
  }

  T cross(const Vector2<T> rhs) const {
    return x * rhs.y - y * rhs.x;
  }
};

}  // namespace maia
