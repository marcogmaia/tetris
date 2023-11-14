#pragma once

#include <cmath>

namespace maia {

template <typename T>
struct Vector2 {
  T x;
  T y;

  using Type = T;

  bool operator==(const Vector2<T>&) const = default;

  constexpr Vector2<T> operator+(const Vector2<T> rhs) const {
    return {x + rhs.x, y + rhs.y};
  };

  constexpr Vector2<T>& operator+=(const Vector2<T> rhs) {
    *this = *this + rhs;
    return *this;
  };

  constexpr Vector2<T> operator-() const {
    return {-x, -y};
  };

  constexpr Vector2<T> operator-(const Vector2<T> rhs) const {
    return *this + (-rhs);
  };

  constexpr T dot(const Vector2<T> rhs) const {
    return x * rhs.x + y * rhs.y;
  }

  constexpr T cross(const Vector2<T> rhs) const {
    return x * rhs.y - y * rhs.x;
  }

  constexpr Vector2<T> Rotate(float angle) {
    float cos = std::cosf(angle);
    float sin = std::sinf(angle);
    return {
        static_cast<T>(x * cos - y * sin),
        static_cast<T>(x * sin + y * cos),
    };
  }
};

}  // namespace maia
