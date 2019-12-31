#include "vector_2.h"
#include "math_utils.h"
#include <cmath>

namespace albinjohansson::wanderer {

using M = MathUtils;

Vector2::Vector2() : Vector2(0, 0) {}

Vector2::Vector2(const Vector2& other) : Vector2(other.x, other.y) {}

void Vector2::Scale(float factor) noexcept {
  x *= factor;
  y *= factor;
}

void Vector2::Norm() noexcept {
  float length = GetLength();
  if (length != 0) {
    x /= length;
    y /= length;
  }
}

void Vector2::Zero() noexcept {
  x = y = 0;
}

void Vector2::Set(const Vector2& other) noexcept {
  x = other.x;
  y = other.y;
}

void Vector2::Set(float x, float y) noexcept {
  this->x = x;
  this->y = y;
}

void Vector2::SetLength(float length) noexcept {
  if (length == 0) {
    x = 0;
    y = 0;
    return;
  }

  float prevLength = GetLength();
  if ((prevLength == 0) || (prevLength == length)) {
    return;
  }
  Scale(length / prevLength);
}

void Vector2::Lerp(const Vector2& target, float alpha) noexcept {
  float invAlpha = 1.0f - alpha;
  this->x = (x * invAlpha) + (target.x * alpha);
  this->y = (y * invAlpha) + (target.y * alpha);
}

void Vector2::Interpolate(const Vector2& target, float alpha) noexcept {
  Lerp(target, alpha * alpha * alpha * (alpha * (alpha * 6 - 15) + 10));
}

void Vector2::Add(const Vector2& other) noexcept {
  x += other.x;
  y += other.y;
}

void Vector2::Add(float x, float y) noexcept {
  this->x += x;
  this->y += y;
}

void Vector2::Sub(const Vector2& other) noexcept {
  x -= other.x;
  y -= other.y;
}

void Vector2::Sub(float x, float y) noexcept {
  this->x -= x;
  this->y -= y;
}

void Vector2::LookAt(const Vector2& target) noexcept {
  auto magnitude = GetLength();
  x = (target.x - x);
  y = (target.y - y);
  Norm();
  Scale(magnitude);
}

void Vector2::LookAt(const Vector2& target, float length) noexcept {
  if (length <= 0) {
    x = 0;
    y = 0;
  } else {
    x = (target.x - x);
    y = (target.y - y);
    Norm();
    Scale(length);
  }
}

void Vector2::Invert() noexcept {
  x *= -1;
  y *= -1;
}

Vector2 Vector2::operator+(const Vector2& other) const noexcept {
  return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const noexcept {
  return Vector2(x - other.x, y - other.y);
}

float Vector2::operator*(const Vector2& other) const noexcept {
  return Dot(other);
}

bool Vector2::operator==(const Vector2& other) const noexcept {
  return M::AlmostEqual(x, other.x)
      && M::AlmostEqual(y, other.y);
}

bool Vector2::operator!=(const Vector2& other) const noexcept {
  return !(*this == other);
}

float Vector2::Dot(const Vector2& other) const noexcept {
  return (x * other.x) + (y * other.y);
}

float Vector2::DistanceTo(const Vector2& other) const noexcept {
  auto xDiff = other.x - x;
  auto yDiff = other.y - y;
  return std::sqrt((xDiff * xDiff) + (yDiff * yDiff));
}

float Vector2::DistanceTo2(const Vector2& other) const noexcept {
  auto xDiff = other.x - x;
  auto yDiff = other.y - y;
  return (xDiff * xDiff) + (yDiff * yDiff);
}

int Vector2::Angle(const Vector2& other) const noexcept {
  return M::Round(M::ToDegrees(std::acos(Dot(other))));
}

float Vector2::GetLength() const noexcept {
  return std::sqrt((x * x) + (y * y));
}

float Vector2::GetLength2() const noexcept {
  return (x * x) + (y * y);
}

bool Vector2::IsZero() const noexcept {
  return M::AlmostEqual(x, 0)
      && M::AlmostEqual(y, 0);
}

bool Vector2::IsUnit() const noexcept {
  return M::AlmostEqual(GetLength2(), 1.0f);
}

}